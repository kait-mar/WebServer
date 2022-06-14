//
// Created by Mouaad Labhairi on 6/7/22.
//

#include "Cgi_parser.hpp"
#include "../ServerConfiguration/Configuration.hpp"

Cgi_parser::Cgi_parser(char *buf, dataConnection *context) : toParse(buf), _context(context){}



void  Cgi_parser::parsing_cgi_response() {


	std::string::size_type len = this->toParse.find_first_of("\n");
	std::string header = this->toParse.substr(0, len);
	this->key = header.substr(0,header.find_first_of(":"));
	this->value = header.substr(header.find_first_of(":") + 1, header.find_first_of("\n"));
//n	this->_env_map[this->key] = this->value;
	this->toParse.erase(0, toParse.find_first_of("\n"));
	// Document Response
	// Set Cookies
	if (this->key == "Set-Cookie")
	{
		while (this->key == "Set-Cookie")
		{
			this->toParse.erase(0, toParse.find_first_of("\n") + 1);
			this->toParse.erase(0, toParse.find_first_of("\n") + 1);
			_context->getResponse()->addCoockie(this->value);
			this->key.clear();
			this->value.clear();
			this->key = this->toParse.substr(0, this->toParse.find_first_of(":"));
			this->value = this->toParse.substr(this->toParse.find_first_of(":") + 1, this->toParse.find_first_of(";") -
																							this->toParse.find_first_of(":"));
			this->toParse.erase(0, toParse.find_first_of("\n"));
		}
	}
	if (this->key == "Content-Type")
	{
		this->content_type = this->key;
		this->content_length = this->toParse.size();
		this->status = 200;
		this->reason_phrase = "OK";
		return;
	}
	// Client Redirect Response
	else if (this->key == "Location")
	{
//	Location	this->_env_map[this->key] = this->value;
		this->location = this->value;
		// Local redirect response
		if (this->value.front() == '/')
		{
			return ;
		}
		this->key.clear();
		this->toParse.erase(0, this->toParse.find_first_of("\n"));
		header = this->toParse.substr(0, this->toParse.find_first_of("\n"));
		this->key = header.substr(0,header.find_first_of(":"));
		// Client Redirect Response with document
		if (this->key == "Content-Type")
		{
			this->value.clear();
			this->value = header.substr(header.find_first_of(":") + 1, header.find_first_of("\n"));
			this->content_type = this->value;
//			this->_env_map[this->key] = this->valueif;
			this->status = 302;
			this->reason_phrase = "Found";
			this->toParse.erase(0, this->toParse.find_first_of("\n"));
			this->content_length = this->toParse.size();
			return;
		}
		this->status = 302;
		this->toParse.erase(this->toParse.begin(), this->toParse.end());
		this->reason_phrase = "Found";
	}
}

std::string  Cgi_parser::get_message_body()
{
	return this->toParse;
}

int 	Cgi_parser::get_status() const{
	return status;
}

const std::string Cgi_parser::get_reason_phrase() const
{
	return reason_phrase;
}

const std::string Cgi_parser::get_location() const
{
	return this->location;
}

const std::string Cgi_parser::get_content_type() const
{
	return this->content_type;
}

std::map<std::string, std::string> Cgi_parser::get_cookies ()
{
	return cookies_map;
}


Cgi_parser::~Cgi_parser() {}


