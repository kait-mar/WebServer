#include "ErrorState.hpp"

#include "../Response/ResponseGenerator.hpp"
#include "SendState.hpp"

ErrorState::ErrorState (unsigned short code, const char *_path): _code (code), path (_path) {}

void ErrorState::handle () {
	ErrorGenerator generator (_code, path);

	context->setResponse (generator.getResponse ());
	context->getOutputBuffer ().setResponseToSend (*(context->getResponse ()));
	context->TranslationTo (new SendState ());
}
