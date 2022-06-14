#include "StartState.hpp"

#include "ParsingState.hpp"
#include "CloseState.hpp"

StartState::StartState () {}

void StartState::handle () {
	if (context->getEvent () == READ) {
		context->getRequest ()->clear ();
		context->getResponse ()->clear ();
		context->TranslationTo (new ParsingState ());
	}
}