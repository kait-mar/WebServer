//
// Created by Mouaad Labhairi on 6/3/22.
//

#include "CgiState.hpp"

#include <iostream>
#include "../Networking/Connections/DataConnection.hpp"
#include "../Request/Request.hpp"
#include "CloseState.hpp"
#include "../Response/Response.hpp"
#include "../Cgi/Cgi_request.hpp"
#include "../Cgi/Cgi_execute.hpp"
#include "../State/SendState.hpp"
#include "../State/ErrorState.hpp"
#include "../Cgi/Cgi_response.hpp"

CgiState::CgiState(std::string &url, std::string&  exec, Server *serv, Location *loc) : _url(url), _exec(exec), _server(serv), _location(loc) {}

void   CgiState::handle (void) {
	OutputBuffer& output  = context->getOutputBuffer();
	Cgi_execute cgi(context, _url, _exec);
	Response *res;


//	cgi.cgi_execute();
	res = cgi.cgi_response();
	if (res == NULL)
	{
		ErrorPages	*error_page;
		std::map <unsigned short, std::string>::iterator it;
		if ((error_page = _location->getSimpleAttribute_<ErrorPages> ()) != NULL
			&& (it = error_page->getErrorPages().find(cgi.get_flags())) != error_page->getErrorPages().end())
			context->TranslationTo (new ErrorState (cgi.get_flags(), it->second.c_str()));
		else if ((error_page = _server->getSimpleAttribute_<ErrorPages> ()) != NULL
			&& (it = error_page->getErrorPages().find(cgi.get_flags())) != error_page->getErrorPages().end())
			context->TranslationTo (new ErrorState (cgi.get_flags(), it->second.c_str()));
		else
			this->context->TranslationTo(new ErrorState(cgi.get_flags()));
		return;
	}
	else
		output.setResponseToSend((*res));
	this->context->TranslationTo(new SendState());
}
