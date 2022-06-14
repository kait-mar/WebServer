#include "SendState.hpp"

#include "CloseState.hpp"
#include "StartState.hpp"

SendState::SendState(bool close): closeAfterSend(close) {}
void SendState::handle () {
	if (context->getEvent ()  == WRITE) {
		if (context->getOutputBuffer ().isSent ()) {
			if (closeAfterSend)
				context->TranslationTo (new CloseState ());
			else
				context->TranslationTo (new StartState ());
		}
		else {
			if (!context->getOutputBuffer().send ())
				context->TranslationTo (new CloseState ());
		}
	}
}

void SendState::CloseAfter (bool close) {
	this->closeAfterSend = close;
}
