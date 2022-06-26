#include "SelectionAlgo.hpp"

SelectionAlgo::SelectionAlgo(): server(NULL), location(NULL) {}

SelectionAlgo::SelectionAlgo(dataConnection* cont): server(NULL), location(NULL), context(cont) {}

SelectionAlgo::~SelectionAlgo() {}

Server  *SelectionAlgo::getServer()
{
    if (server != NULL)
        return server;
    Listen	*listen;
	ServerNames	*server_name;
	HeaderFields	&hf = context->getRequest()->getHeaderFields();
    std::vector<Server*> servers (Configuration::instance()->getConfigurations()->getSubComponents_ <Server>() );
	Server	*default_ = servers[0];
	Host	host(hf["host"]); host.check();

	// selection by port, then by server_name
	for (std::vector<Server*>::iterator i = servers.begin(); i != servers.end(); i++)
	{
		listen = (*i)->getSimpleAttribute_<Listen> ();
		if (host._prt.getPort() != listen->getPort())
		{
			servers.erase(i);
			i--;
		}
	}
//	if (servers.size() == 1)
//    {
//        server = servers[0];
//        return server ;
//    }

	if (host.is_server_name && host._host != "localhost")
	{
		for (std::vector<Server*>::iterator it = servers.begin(); it != servers.end(); it++)
		{
			server_name = (*it)->getSimpleAttribute_<ServerNames> ();
			if (server_name->getNames().find(host._host) == server_name->getNames().end())
			{
				it = servers.erase(it);
				it--;
			}
		}
	}
	if (servers.size() == 1 || servers.size() == 2)
        server = servers[0];
	
	if (servers.size() == 0)
		server = default_;
	return server;
}

Location    *SelectionAlgo::getLocation()
{
    if (location != NULL)
        return location;
    // from uri
	std::vector<Location *> locations (server->getSubComponents_ <Location>());
	RequestLine	line = context->getRequest()->getRequestLine();
	std::string	ressource = "/";
	URI	uri = line.getURL();
	if (uri.ressource() != "")
	{
		std::string s = ltrim(uri._ressource, "/");
		std::vector<std::string>	vec = split(s, "/");
		if (vec.size() && vec[0].find(".") != std::string::npos)
			ressource = "/";
		else if (vec.size() >= 1)
			ressource = "/" + vec[0];
	}
	for (size_t i = 0; i < locations.size(); i++)
	{
		if (ressource == locations[i]->get_suf())
		{
			location = locations[i];
            break ;
		}
	}
    return location;
}

Return       *SelectionAlgo::checkReturn (int flag)
{
    Return *ret = NULL;

    if (flag == IN_SERVER)
        ret = server->getSimpleAttribute_<Return> ();
    else if (flag == IN_LOCATION)
        ret = location->getSimpleAttribute_<Return> ();
    return ret;
}

int	SelectionAlgo::default_()
{
	std::string root = server->getSimpleAttribute_<Root> ()->getRoot();
	if (root[root.size() - 1] != '/')
		root += "/";
	RequestLine	line = context->getRequest()->getRequestLine();
	std::string	ressource = "/";
	URI	uri = line.getURL();
	if (uri.ressource() != "")
	{
		std::string s = ltrim(uri._ressource, "/");
		size_t pos = s.find_first_of("/");
		s = s.substr(pos + 1, s.size());
		s = root + s;
		if (access(s.c_str(), F_OK) != 0)
		{
			context->getResponse()->setStatusCode("404");
			return 404;
		}
		if (is_directory(s) || access(s.c_str(), R_OK) != 0)
		{
			context->getResponse()->setStatusCode("403");
			return 403;
		}
		int	file;
		if ((file = open(s.c_str(), O_RDONLY)) < 0)
		{
			context->getResponse()->setStatusCode("500");
			return 403;
		}
		context->getResponse()->getPayload().setFile(file);
		::close(file);
		context->getResponse()->setVersion("HTTP/1.1");
		context->getResponse()->setStatusCode("200");
		size_t ops;
		std::string	ext;
		if ((ops = s.find_last_of(".")) != std::string::npos)
			ext = s.substr(ops + 1, s.size());
		else
			ext = "xxx";
		std::string	mim =  Configuration::mimeType ("server");
		context->getResponse()->getHeaderfields()["Server"] = "Webserv";
		context->getResponse()->getHeaderfields()["Content-Type"] = Configuration::mimeType(ext);
		context->getResponse()->getHeaderfields()["Content-Length"] = std::string(::std::to_string(context->getResponse()->getPayload().size()));
	}
	return (200);
}
