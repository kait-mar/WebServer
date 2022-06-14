//
// Created by Mouaad Labhairi on 5/30/22.
//

#include "Cgi_request.hpp"


Cgi_request::Cgi_request() {

}
Cgi_request::~Cgi_request() {

}

bool 		Cgi_request::match(std::string check)
{
	const char* meta_variables[17] = {"auth_type", "content_lenght","content_type", "gateway_interface",
											   "path_info", "path_translated", "query_string", "remote_addr",
											   "remote_host", "remote_ident", "remote_user", "request_method",
											   "script_name", "server_name", "server_port", "server_protocol",
											   "server_software"};
	std::vector<std::string> meta_arr(meta_variables, meta_variables + 17);
	for (std::vector<std::string>::iterator it = meta_arr.begin() ; it != meta_arr.end(); it++)
	{
		if (check == *it)
			return true;
	}
	return false;
}

std::map<std::string, std::string> Cgi_request::set_environment_variables(dataConnection* context) {

	std::string variable;
	HeaderFields::headers env ;
	std::string request;
	this->requestLine = context->getRequest()->get_requestLine();
	this->headerFields = context->getRequest()->get_headerFields();
	this->messageBody = context->getRequest()->getRequestBody().body();
	env = headerFields->get_hf();
	std::map<std::string, std::string>::iterator iter = env.begin();
	while (iter != env.end())
	{
		if (match(iter->first))
		{
			variable = iter->first;
			std::transform(variable.begin(), variable.end(),variable.begin(), ::toupper);
			for(int i = 0 ; variable[i] ; i++)
			{
				if (variable[i] == '-')
					variable[i] = '_';
			}
		}
		else
		{
			variable = "HTTP_";
			variable += iter->first;
//			variable = iter->first;
			std::transform(variable.begin(), variable.end(),variable.begin(), ::toupper);
			for(int i = 0 ; variable[i] ; i++)
			{
				if (variable[i] == '-')
					variable[i] = '_';
			}
		}
		environment_variable[variable] = iter->second;
		iter++;
	}
	variable = "REQUEST_METHOD";
	for(int i = 0 ; variable[i] ; i++)
	{
		if (variable[i] == '-')
			variable[i] = '_';
	}
	request = requestLine->getMethod();
	std::transform(request.begin(), request.end(),request.begin(), ::toupper);
	environment_variable[variable] = request;
	return environment_variable;
}


