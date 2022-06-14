#include "RedirectGenerator.hpp"

RedirectGenerator::RedirectGenerator (unsigned short code_, const std::string& path_): code (code_), path (path_) {}
RedirectGenerator::~RedirectGenerator () {}

void RedirectGenerator::add_response_line () {
	this->response->setVersion ("HTTP/1.1");
	this->response->setStatusCode (std::to_string (code));
	this->response->setReasonPhrase (Configuration::codeToReasonPhrase (code));
}

void RedirectGenerator::add_header_fields () {
	this->response->addHeaderField ("Server", Configuration::serverName ());
	this->response->addHeaderField ("Location", path);
	this->response->addHeaderField ("Date", httpDateTime ());
	this->response->addHeaderField ("Connection", "keep-alive");
}
