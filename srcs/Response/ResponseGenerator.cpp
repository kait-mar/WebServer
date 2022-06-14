#include "ResponseGenerator.hpp"


#include "../ServerConfiguration/Configuration.hpp"
#include "../utility/time_utility.hpp"
#include <fcntl.h>
#include "ErrorPageGenerator.hpp"

ResponseGenerator::ResponseGenerator () {
	response = new Response ();
}
ResponseGenerator::~ResponseGenerator () {
	delete response;
}

Response *ResponseGenerator::getResponse () {
	this->build ();
	Response *res = this->response;
	this->response = 0x0;
	return res;
}

ErrorGenerator::ErrorGenerator (unsigned short _code, const char *_path): code (_code), path (_path) {}

void ErrorGenerator::add_response_line () {
	this->response->setVersion ("HTTP/1.1");
	this->response->setStatusCode (std::to_string (code));
	this->response->setReasonPhrase (Configuration::codeToReasonPhrase (code));
}

void ErrorGenerator::add_header_fields () {
	this->response->addHeaderField ("Server", Configuration::serverName ());
	this->response->addHeaderField ("Date", httpDateTime ());
	this->response->addHeaderField ("Connection", "close");
}

void ErrorGenerator::add_payload () {
	int fd = -1;

	std::string Content_type = "text/html";
	if (path) {
		fd = ::open (path, O_RDONLY);
		if (fd != -1) {
			this->response->getPayload ().setFile (fd);
			std::string p (path);
			if (p.find_last_of (".") != std::string::npos)
				Content_type = Configuration::mimeType (p.substr (p.find_last_of (".") + 1));
		}
	}
	if (fd == -1)
		this->response->getPayload ().setBuffer (ErrorPageGenerator (code));
	this->response->addHeaderField ("Content-Type", Content_type);
	this->response->addHeaderField ("Content-length", std::to_string (this->response->getPayload ().size ()));
}
