//
// Created by Mouaad Labhairi on 6/6/22.
//

#include "Cgi_response.hpp"
#include "../utility/time_utility.hpp"


//hppResponseGenerator::ResponseGenerator () {
//	response = new Response ();
//}
//ResponseGenerator::~ResponseGenerator () {
//	delete response;
//}
//
//Response *ResponseGenerator::getResponse () {
//	Response *res = this->response;
//	this->response = 0x0;
//	return res;
//}
//
//
//
//Cgi_response::Cgi_response(int status_code, std::map<std::string, std::string> res) : _status_code(status_code), _res_env(res);
//
//void Cgi_response::add_response_line() {
//	this->response->setVersion("HTTP/1.1");
//	this->response->setStatusCode(std::to_string(200));
////200	this->response->setReasonPhrase (Configuration::codeToReasonPhrase (200));
//}
//
//void Cgi_response::add_header_fields() {
//	this->response->addHeaderField ("Server", Configuration::serverName ());
//	this->response->addHeaderField ("Date", httpDateTime ());
//	this->response->addHeaderField ("Content-Type", _res_env["CONTENT_TYPE"]);
//	this->response->addHeaderField("path-info", _res_env["PATH_INFO"]);
//}
