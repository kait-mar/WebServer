//
// Created by Mouaad Labhairi on 5/30/22.
//

#ifndef WEB_SERVER_CGI_REQUEST_HPP
#define WEB_SERVER_CGI_REQUEST_HPP

#include "../Request/Request.hpp"
#include "../Request/HeaderFields.hpp"
#include "../Request/RequestLine.hpp"
#include "../Networking/Connections/DataConnection.hpp"


class Cgi_request {

private:
	RequestLine *requestLine;
	HeaderFields	*headerFields;
	std::map<std::string, std::string> environment_variable;
	bool match(std::string);


protected:
	std::string 	messageBody;
public:
	Cgi_request();
	~Cgi_request();
	std::map<std::string, std::string> set_environment_variables(dataConnection *context);
};


#endif //WEB_SERVER_CGI_REQUEST_HPP
