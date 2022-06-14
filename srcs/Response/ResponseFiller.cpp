#include "ResponseFiller.hpp"

ResponseFiller::ResponseFiller(): error(0), __is_cgi(0) {}

ResponseFiller::ResponseFiller(dataConnection* data, Server* serv, Location* loc, Response* resp):
context(data), server(serv), location(loc), response(resp), error(0), __is_cgi(0) {}

ResponseFiller::~ResponseFiller() {}

int		ResponseFiller::getError()	{	return error;	}

void    ResponseFiller::fill()
{
    RequestLine	request_line = context->getRequest()->getRequestLine();
	HeaderFields	request_hf = context->getRequest()->getHeaderFields();
	if (request_line.getMethod() == "GET") //lowercase ??
	{
		int ret;
		if ((ret = execute_get(request_line)) != 200 || ret == 98)	
			error = ret;
	}	
	else if (request_line.getMethod() == "POST") //lowercase ??
	{
		// int ret;
		// if ((ret = execute_post(request_line)) != 201 || ret == 98)
			error = execute_post(request_line);
	}
	else if (request_line.getMethod() == "DELETE") //lowercase ??
	{
		// int ret;
		// if ((ret = execute_delete(request_line)) != 204 || ret == 98)		
			error = execute_delete(request_line);
	}
}

int		ResponseFiller::execute_get(RequestLine& line)
{
	__is_cgi = 0;
	std::string	ressource = path_file(line, server, location);
	int	file;
	file = ::open(ressource.c_str(), O_RDONLY);
	if (file < 0) 
	{
		response->setStatusCode("404");
		return (404);
	}
	if (is_directory(ressource))
	{
		close(file);
		if (ressource[ressource.size() - 1] != '/')
			ressource += "/";
			Index	*ind ;
			if ((ind = location->getSimpleAttribute_<Index> () ) != NULL)
			{
				std::string	index = chooseIndex(ind->getIndexes());
				if (index != "")
				{
					std::cout << index << std::endl;
					CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
					if (cgi_pass != NULL)
					{
						cgi = index;
						size_t	ops;
						std::string	ext;
						if ((ops = index.find_last_of(".")) != std::string::npos)
							ext = index.substr(ops , index.size());
						if (cgi_pass->get_map().find(ext) != cgi_pass->get_map().end())
						{
							__is_cgi = 1;
							_cgi_exec = cgi_pass->get_map()[ext];
							return (98);
						}
						else
						{
							response->setStatusCode("404");
							return (404);
						}
					}
					fill_body(index);
					response->setStatusCode("200");
					fill_headers(index);
				}
				else
				{
					response->setStatusCode("404");
					return (404);
				}
			}
			else if ((ind = server->getSimpleAttribute_<Index> ()) != NULL)
			{
				std::string	index = chooseIndex(ind->getIndexes(), IN_SERVER);
				if (index != "")
				{
					CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
					if (cgi_pass != NULL)
					{
						cgi = index;
						size_t	ops;
						std::string	ext;
						if ((ops = index.find_last_of(".")) != std::string::npos)
							ext = index.substr(ops , index.size());
						if (cgi_pass->get_map().find(ext) != cgi_pass->get_map().end())
						{
							__is_cgi = 1;
							_cgi_exec = cgi_pass->get_map()[ext];
							return (98);
						}
						else
						{
							response->setStatusCode("404");
							return (404);
						}
					}
					fill_body(index);
					response->setStatusCode("200");
					fill_headers(index);
				}
				else
				{
					response->setStatusCode("404");
					return (404);
				}
			}
			else
			{
				AutoIndex	*auto_index;
				if ((auto_index = location->getSimpleAttribute_<AutoIndex> ()) != NULL)
				{
					if (auto_index->getAutoIndex() == "off")
					{
						response->setStatusCode("403");
						return (403);
					}
					else
					{
						std::string list = list_directory(ressource);
						response->setStatusCode("200");
						response->getPayload().setBuffer(list);
						fill_headers(list);
						response->getHeaderfields()["Content-Type"] = Configuration::mimeType("txt");
					}
				}
				else if ((auto_index = server->getSimpleAttribute_<AutoIndex> ()) != NULL)
				{
					if (auto_index->getAutoIndex() == "off")
					{
						response->setStatusCode("403");
						return (403);
					}
					else
					{
						std::string list = list_directory(ressource);
						response->setStatusCode("200");
						response->getPayload().setBuffer(list);
						fill_headers(list);
						response->getHeaderfields()["Content-Type"] = Configuration::mimeType("txt");
					}
				}
				else
				{
					response->setStatusCode("403");
					return (403);
				}
			}
	}
	else //is_file
	{
		CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
		if (cgi_pass != NULL)
		{
			close(file);
			size_t	ops;
			cgi = ressource;
			std::string	ext;
			if ((ops = ressource.find_last_of(".")) != std::string::npos)
				ext = ressource.substr(ops , ressource.size());
			if (cgi_pass->get_map().find(ext) != cgi_pass->get_map().end())
			{
				_cgi_exec = cgi_pass->get_map()[ext];
				__is_cgi = 1;
				return (98);
			}
			else
			{
				response->setStatusCode("404");
				return (404);
			}
		}
		response->getPayload().setFile(file);
		::close(file);
		response->setStatusCode("200");
		fill_headers(ressource);
	}
	response->setVersion("HTTP/1.1");
	return (200);
}


int		ResponseFiller::execute_post(RequestLine &line)
{
	std::string	ressource = path_file(line, server, location);
	Upload	*upl = location->getSimpleAttribute_<Upload> ();
	if (upl != NULL)
	{
		std::string file = upload_file(upl->getRoot(), line, location);
		if (file[file.size() - 1] == '/')
		{
			response->setStatusCode("403");
			return 403;
		}
		if (access(file.c_str(), F_OK) != 0)
		{
			response->setStatusCode("406"); //internal server error
			return 406;
		}
		int fd = ::open(file.c_str() , O_CREAT | O_RDWR | O_TRUNC);
		if (fd < 0)
		{
			response->setStatusCode("500"); //internal server error
			return 500;
		}
		std::string	buffer = context->getRequest()->getRequestBody().body();
		::write(fd, buffer.c_str(), buffer.size());
		response->setStatusCode("201");
		fill_headers(ressource);
		response->setVersion("HTTP/1.1");
		close(fd);
		return (201);
	}
	else
	{
		int fd_;
		if ((fd_ = ::open(ressource.c_str(), O_RDWR)) < 0)
		{
			response->setStatusCode("404");
			return 404;
		}
		if (is_directory(ressource))
		{
			close(fd_);
			Index	*ind ;
			if ((ind = location->getSimpleAttribute_<Index> () ) != NULL)
			{
				std::string	index = chooseIndex(ind->getIndexes());
				if (index != "")
				{
					CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
					if (cgi_pass != NULL)
					{
						cgi = index;
						size_t	ops;
						std::string	ext;
						if ((ops = index.find_last_of(".")) != std::string::npos)
							ext = index.substr(ops , index.size());
						if (cgi_pass->get_map().find(ext) != cgi_pass->get_map().end())
						{
							__is_cgi = 1;
							_cgi_exec = cgi_pass->get_map()[ext];
							return (98);
						}
						else
						{
							response->setStatusCode("404");
							return (404);
						}
					}
					else
					{
						response->setStatusCode("403");
						return 403;
					}
				}
				else
				{
					response->setStatusCode("404");
					return (404);
				}
			}
			else if ((ind = server->getSimpleAttribute_<Index> ()) != NULL)
			{
				std::string	index = chooseIndex(ind->getIndexes(), IN_SERVER);
				if (index != "")
				{
					CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
					if (cgi_pass != NULL)
					{
						cgi = index;
						size_t	ops;
						std::string	ext;
						if ((ops = ressource.find_last_of(".")) != std::string::npos)
							ext = ressource.substr(ops , ressource.size());
						if (cgi_pass->get_map().find(ext) != cgi_pass->get_map().end())
						{
							__is_cgi = 1;
							_cgi_exec = cgi_pass->get_map()[ext];
							return (98);
						}
						else
						{
							response->setStatusCode("404");
							return (404);
						}
					}
					else
					{
						response->setStatusCode("403");
						return 403;
					}
				}
				else
				{
					response->setStatusCode("404");
					return (404);
				}
			}
			else
			{
				response->setStatusCode("403");
				return 403;
			}
		}
		else
		{
			close(fd_);
			CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
			if (cgi_pass != NULL)
			{
				cgi = ressource;
				size_t	ops;
				std::string	ext;
				if ((ops = ressource.find_last_of(".")) != std::string::npos)
					ext = ressource.substr(ops , ressource.size());
				if (cgi_pass->get_map().find(ext) != cgi_pass->get_map().end())
				{
					__is_cgi = 1;
					_cgi_exec = cgi_pass->get_map()[ext];
					return (98);
				}
				else
				{
					response->setStatusCode("404");
					return (404);
				}
			}
			else
			{
				response->setStatusCode("403");
				return 403;
			}
		}
	}
}

int		ResponseFiller::execute_delete(RequestLine& line)
{
	CgiPass	*cgi_pass = location->getSimpleAttribute_<CgiPass> ();
	if (cgi_pass != NULL)
	{
		response->setStatusCode("501");
		return (501);
	}
	std::string	ressource = path_file(line, server, location); //what if it's a folder ?
	if (access(ressource.c_str(), F_OK) != 0) 
	{
		response->setStatusCode("404");
		return (404);
	}
	if (!is_directory(ressource))
	{
		if (access(ressource.c_str(), W_OK) != 0) 
		{
			response->setStatusCode("403");
			return (403);
		}
		if (remove(ressource.c_str()) == 0)
		{
			response->setStatusCode("204");
			response->getHeaderfields()["Server"] = "Webserv";
			response->setVersion("HTTP/1.1");
			return (204);
		}
		else
		{
			response->setStatusCode("500");
			return 500;
		}
	}
	else
	{
		std::string ret = delete_folder_content(ressource);
		response->setStatusCode(ret);
		response->getHeaderfields()["Server"] = "Webserv";
		return (::atoi(ret.c_str()));
	}
}

void	ResponseFiller::fill_headers(std::string ressource)
{
	size_t ops;
	std::string	ext;
	if ((ops = ressource.find_last_of(".")) != std::string::npos)
		ext = ressource.substr(ops + 1, ressource.size());
	else
		ext = "xxx";
	std::string	mim =  Configuration::mimeType ("server");
	response->getHeaderfields()["Server"] = "Webserv";
	response->getHeaderfields()["Content-Type"] = Configuration::mimeType(ext);
	// response->getHeaderfields()["Connection"] = "Keep-Alive"; // depends on client connection !!??
	response->getHeaderfields()["Content-Length"] = std::string(::std::to_string(response->getPayload().size()));
}

std::string	ResponseFiller::delete_folder_content(std::string ressource)
{
	DIR *d;
	struct dirent *dir;
	if (ressource[ressource.size() - 1] != '/')
		ressource += "/";
	d = opendir(ressource.c_str());
	if (d) {
	while ((dir = readdir(d)) != NULL) {
		std::string	s = ressource + std::string(dir->d_name);
		if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")
			&& access(s.c_str(), W_OK) != 0) 
		{
			return ("403");
		}
		if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..") && remove(s.c_str()) != 0)
		{
			return ("500");
		}
	}
	closedir(d);
	}
	return ("204");
}

std::string	ResponseFiller::path_file(RequestLine &line, Server* server, Location* location)
{
	Root	*root;
	std::string	ressource = "/";
	ressource = line.getURL().file(location->get_suf());
	// std::vector<std::string>	str = split(line.getURL().file(location->get_suf()), "/");
	// for (size_t i = 1; i < str.size(); i++)
	// {
	// 	ressource +=  str[i];
	// 	if (i != str.size() - 1)
	// 		ressource += "/";
	// }
	if ((root = location->getSimpleAttribute_<Root> ()) != NULL)
		ressource = root->getRoot() + ressource;
	else
	{
		root = server->getSimpleAttribute_<Root> ();
		ressource = root->getRoot() + ressource;
	}
	return (ressource);
}

std::string	ResponseFiller::upload_file(std::string upstream, RequestLine &line, Location* location)
{
	std::string	ressource = "/";
	ressource = line.getURL().file(location->get_suf());
	ressource = upstream + ressource;
	return (ressource);
}

void		ResponseFiller::fill_body(std::string ressource)
{
	int	file = ::open(ressource.c_str(), O_RDONLY);
	response->getPayload().setFile(file);
	close(file);
}

std::string ResponseFiller::chooseIndex(std::vector<std::string> indexes, int flag)
{
	std::string	root;
	if (flag == IN_SERVER)
		root = server->getSimpleAttribute_<Root> ()->getRoot();
	else if (flag == IN_LOCATION)
		root = location->getSimpleAttribute_<Root> ()->getRoot();
	else
	{
		Root *r  = location->getSimpleAttribute_<Root> ();
		if (r == NULL)
			r = server->getSimpleAttribute_<Root> ();
		root = r->getRoot();
	}
	if (root[root.size() - 1] != '/')
		root += "/";
	for (size_t i = 0; i < indexes.size(); i++)
	{
		// if (::open((root + indexes[i]).c_str(), O_RDONLY) >= 0)
		if (access((root + indexes[i]).c_str(), F_OK) == 0)
			return root + indexes[i];
	}
	return "";
}

std::string	ResponseFiller::list_directory(std::string str)
{
	std::string	buffer = "this is a directory, and its content is:\n";
	DIR *d;
	struct dirent *dir;
	d = opendir(str.c_str());
	int	empty = 1;
	if (d) {
	while ((dir = readdir(d)) != NULL) {
		empty = 0;
		buffer += std::string(dir->d_name) + "\n";
	}
	closedir(d);
	}
	if (empty == 1)
		buffer = "this is an empty directory\n";
	return buffer;
}

int	ResponseFiller::is_cgi()	{	return __is_cgi;	}
std::string	&ResponseFiller::cgi_path()	{	return cgi;	}
std::string	&ResponseFiller::cgi_exec()	{	return _cgi_exec;	}
