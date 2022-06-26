#include "ParsingState.hpp"

#include "CloseState.hpp"
#include "ErrorState.hpp"
#include "PayloadState.hpp"
#include "ExecuteState.hpp"



ParsingState::ParsingState () {
	static FiltersManager *filtersManager;
	if (!filtersManager) {
		filtersManager = new FiltersManager ;
		filtersManager->addFilter (new TransferEncodingFilter ());
		filtersManager->addFilter (new MalFormedUrl ());
		filtersManager->addFilter (new PostWithNoBody ());
		filtersManager->addFilter (new BodySizeTooLarge ());
	}
	filters = filtersManager;
}

#define MAXLINESIZE 1024

void ParsingState::handle () {
	InputBuffer& buffer = context->getInputBuffer ();
    if (context->getEvent () == READ) {
		if (!buffer.read (context->getFd ())) {
			context->TranslationTo (new CloseState ());
			return;
		}
    }
    if (!(context->getRequest ()->isParsed ())) {
		std::string		line;
		if (buffer.getNextLine (line)){
			if (context->getRequest ()->parse (line) == false) {
				context->TranslationTo (new ErrorState (400));
			}
		}
		else if (buffer.size () > MAXLINESIZE)
			context->TranslationTo (new ErrorState (400));
    }
    else {
		if (this->filters) {
			unsigned short code = this->filters->filter (*(context->getRequest ()));
			if (code) {
				context->TranslationTo (new ErrorState (code));
				return;
			}
		}
		context->getRequest()->print ();
		if (context->getRequest()->getHeaderFields ().has ("Content-Length")) {
			std::cout << "here\n" << std::endl;
			int size = ::atoi ((context->getRequest ()->getHeaderFields()["Content-Length"]).c_str ());
			context->TranslationTo (new PayloadState (RAW, size));
		}
		else if (context->getRequest()->getHeaderFields ().has ("Transfer-Encoding")){
			context->TranslationTo (new PayloadState (CHUNKED));
		}
		else
			context->TranslationTo (new ExecuteState ());
	}
}
