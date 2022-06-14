//
// Created by Mouaad Labhairi on 6/6/22.
//

#ifndef WEB_SERVER_CGI_ERROR_HPP
#define WEB_SERVER_CGI_ERROR_HPP

#include "Cgi_execute.hpp"
#include "Cgi_request.hpp"



class Cgi_error_request : public Cgi_request{
public:
	Cgi_error_request(Cgi_request);
	~Cgi_error_request();

};


#endif //WEB_SERVER_CGI_ERROR_HPP
