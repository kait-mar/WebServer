//
// Created by Mouaad Labhairi on 6/7/22.
//

#ifndef WEB_SERVER_CGI_PARSER_HPP
#define WEB_SERVER_CGI_PARSER_HPP

#include <iostream>
#include <map>
#include "../InputBuffer/InputBuffer.hpp"
#include "../Networking/Connections/DataConnection.hpp"

class Cgi_parser {

private:
	std::string toParse;
//	std::map<std::string, std::string>& _env_map;
	std::string key;
	std::string value;
	std::string reason_phrase;
	std::string content_type;
	std::string location;
	unsigned int status;
	unsigned  int content_length;
	std::map<std::string, std::string> cookies_map;

public:

	dataConnection *_context;
	Cgi_parser(char *buf, dataConnection *data);
	~Cgi_parser();
	 void parsing_cgi_response();
	 std::string get_message_body();
	  int get_status() const;
	 const std::string get_reason_phrase() const;
	const std::string get_content_type() const ;
	const std::string get_location() const;
	std::map<std::string, std::string> get_cookies ();

};


#endif //WEB_SERVER_CGI_PARSER_HPP
