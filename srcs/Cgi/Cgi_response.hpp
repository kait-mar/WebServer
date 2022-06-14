//
// Created by Mouaad Labhairi on 6/6/22.
//

#ifndef WEB_SERVER_CGI_RESPONSE_HPP
#define WEB_SERVER_CGI_RESPONSE_HPP

#include "../Response/ResponseGenerator.hpp"
#include "Cgi_execute.hpp"

class Cgi_response : public ResponseGenerator {

private:
	unsigned short _status_code;
	std::map<std::string, std::string> _res_env;

public:
	Cgi_response(std::string, std::map<std::string, std::string>);
	~Cgi_response();
	void add_response_line ();
	void add_header_fields ();
	void add_payload ();

};


#endif //WEB_SERVER_CGI_RESPONSE_HPP
