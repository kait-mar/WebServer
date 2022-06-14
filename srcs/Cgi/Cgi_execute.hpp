//
// Created by Mouaad Labhairi on 5/31/22.
//

#ifndef WEB_SERVER_CGI_EXECUTE_HPP
#define WEB_SERVER_CGI_EXECUTE_HPP

#include <unistd.h>
#include <string.h>
#include <cstring>
#include "Cgi_request.hpp"
#include "../OutputBuffer/OutputBuffer.hpp"
#include "../Response/Response.hpp"
#include "../Networking/Connections/DataConnection.hpp"


class Cgi_execute : public Cgi_request{

public:
	Cgi_execute();
	Cgi_execute(dataConnection *context, std::string& path, std::string& exec);
	~Cgi_execute();

	void	cgi_execute();
	Response	*cgi_response();
	std::map<std::string, std::string> env_map;
	char 	*buf;
	int 	get_flags ();

private:
	int 	flags;
	dataConnection *_context;
	int 			fd[2];
	std::string		_path;
	std::string		_exec;
	char**	fill_env(std::map<std::string, std::string> env_map);
	void 	cgi_method_get(void);
	void 	cgi_method_post(void);
	void 	add_response_variables(URI);
	std::string gen_random(const int len);

};


#endif //WEB_SERVER_CGI_EXECUTE_HPP
