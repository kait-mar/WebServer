#include "PayloadState.hpp"


#include "CloseState.hpp"
#include "ErrorState.hpp"
#include "ExecuteState.hpp"
#include "../TransferEncoding/TransferEncoding.hpp"

PayloadState::PayloadState (TRANSFERTYPE type_, unsigned int lenght_) {
	type = type_;
	lenght = lenght_;
	encoding = (type_ == RAW)? nullptr: new TransferEncoding ();
}

PayloadState::~PayloadState () {
	if (encoding)
		delete encoding;
}

void PayloadState::handle () {
	InputBuffer& buffer = context->getInputBuffer ();
	Payload& 	payload = context->getRequest()->getRequestBody ();
	if (context->getEvent () == READ) {
		if (!buffer.read (context->getFd ())) {
			context->TranslationTo (new CloseState ());
			return;
		}
	}
	switch (type) {
		case RAW:
			if (buffer.size () >= lenght) {
				payload.setBuffer (buffer.getPart (lenght));
				context->TranslationTo (new ExecuteState ());
			}
			break;
		case CHUNKED:
			if (encoding->Decode (*context)) {
				if (encoding->isComplete ()) {
					context->getRequest ()->getHeaderFields().remove ("Transfer-Encoding");
					context->getRequest ()->getHeaderFields().add ("Content-Length", std::to_string (payload.size ()));
					context->TranslationTo (new ExecuteState ());
				}
			}
			else
				context->TranslationTo (new ErrorState (400));
	}
}