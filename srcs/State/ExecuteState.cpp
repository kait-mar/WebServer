#include "ExecuteState.hpp"
#include <iostream>
#include "CloseState.hpp"
#include "SendState.hpp"
#include "../Response/Response.hpp"
#include "../Cgi/Cgi_request.hpp"
#include "../Cgi/Cgi_execute.hpp"
#include "../State/SendState.hpp"
#include "../State/ErrorState.hpp"
#include "../State/CgiState.hpp"
#include <fcntl.h>
#include "../Response/ResponseGenerator.hpp"
#include "../Response/RedirectGenerator.hpp"
#include "../SelectionAlgo/SelectionAlgo.hpp"
// #include "ErrorState.hpp"
#include "../ServerConfiguration/Configuration.hpp"


ExecuteState::ExecuteState () {}

void   ExecuteState::handle (void) {
	SelectionAlgo	select(context);
	Return			*ret;


	Server	*serv = select.getServer();
	if (serv == NULL) {
		context->TranslationTo (new ErrorState (404));
		return ;
	}
	if ((ret = select.checkReturn(IN_SERVER)))
	{
		RedirectGenerator generator (ret->getCode (), ret->getPath ());
		context->setResponse (generator.getResponse ());
		context->TranslationTo (new SendState ());
		return;
	}
	Location	*loc = select.getLocation();
	if (loc == NULL) {
		ErrorPages	*error_page;
		std::map <unsigned short, std::string>::iterator it;
		if ((error_page = serv->getSimpleAttribute_<ErrorPages> ()) != NULL
			&& (it = error_page->getErrorPages().find(404)) != error_page->getErrorPages().end())
			context->TranslationTo (new ErrorState (404, it->second.c_str()));
		else
			context->TranslationTo (new ErrorState (404));
		return ;
	}
	else
	{
		if ((ret = select.checkReturn(IN_LOCATION)))
		{
			RedirectGenerator generator (ret->getCode (), ret->getPath ());
			generator.build();
			context->setResponse (generator.getResponse ());
			context->getOutputBuffer ().setResponseToSend (*(context->getResponse ()));
			context->TranslationTo (new SendState ());
			return;
		}
		AllowedMethods	*allowed_method = loc->getSimpleAttribute_<AllowedMethods> ();
		std::set<std::string> implemented; implemented.insert("GET"); implemented.insert("POST");implemented.insert("DELETE");
		if (implemented.find(context->getRequest()->get_requestLine()->getMethod()) == implemented.end())
		{
			ErrorPages	*error_page;
			std::map <unsigned short, std::string>::iterator it;
			if ((error_page = loc->getSimpleAttribute_<ErrorPages> ()) != NULL
				&& (it = error_page->getErrorPages().find(501)) != error_page->getErrorPages().end())
				context->TranslationTo (new ErrorState (501, it->second.c_str()));
			else if ((error_page = serv->getSimpleAttribute_<ErrorPages> ()) != NULL
				&& (it = error_page->getErrorPages().find(501)) != error_page->getErrorPages().end())
				context->TranslationTo (new ErrorState (501, it->second.c_str()));
			else
				context->TranslationTo (new ErrorState (501));
			return ;
		}
		if (allowed_method->getMethods().find(context->getRequest()->get_requestLine()->getMethod()) == allowed_method->getMethods().end())
		{
			ErrorPages	*error_page;
			std::map <unsigned short, std::string>::iterator it;
			if ((error_page = loc->getSimpleAttribute_<ErrorPages> ()) != NULL
				&& (it = error_page->getErrorPages().find(405)) != error_page->getErrorPages().end())
				context->TranslationTo (new ErrorState (405, it->second.c_str()));
			else if ((error_page = serv->getSimpleAttribute_<ErrorPages> ()) != NULL
				&& (it = error_page->getErrorPages().find(405)) != error_page->getErrorPages().end())
				context->TranslationTo (new ErrorState (405, it->second.c_str()));
			else
				context->TranslationTo (new ErrorState (405));
			return ;
		}
		ResponseFiller		responseFiller(context, serv, loc, context->getResponse());
		responseFiller.fill();
		if (responseFiller.is_cgi())
		{
			context->TranslationTo(new CgiState(responseFiller.cgi_path(), responseFiller.cgi_exec(), serv, loc));
			return ;
		}
		if (responseFiller.getError())
		{
			ErrorPages	*error_page;
			std::map <unsigned short, std::string>::iterator it;
			if ((error_page = loc->getSimpleAttribute_<ErrorPages> ()) != NULL
				&& (it = error_page->getErrorPages().find(responseFiller.getError())) != error_page->getErrorPages().end())
				context->TranslationTo (new ErrorState (responseFiller.getError(), it->second.c_str()));
			else if ((error_page = serv->getSimpleAttribute_<ErrorPages> ()) != NULL
				&& (it = error_page->getErrorPages().find(responseFiller.getError())) != error_page->getErrorPages().end())
				context->TranslationTo (new ErrorState (responseFiller.getError(), it->second.c_str()));
			else
				context->TranslationTo (new ErrorState (responseFiller.getError()));
			return ;
		}
	}

	OutputBuffer& output  = context->getOutputBuffer();
    output.setResponseToSend(*context->getResponse());
	if (context->getRequest()->get_headerFields()->getHeader("Connection") == "Keep-Alive")
		context->TranslationTo (new SendState (false));
	else
		context->TranslationTo (new SendState ());
}
