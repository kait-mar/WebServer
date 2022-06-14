#include "TransferEncoding.hpp"

#include <sstream>
#define MAXLENGHTSIZECHUNK 		8

TransferEncoding::TransferEncoding (): state_ (WAITINGFORSIZE) {}

bool TransferEncoding::isComplete () const {
	return (state_ == COMPLETE);
}

bool TransferEncoding::Decode (dataConnection &context) {
	std::string 	chunk;
	InputBuffer& 	buffer = context.getInputBuffer ();
	Request* 		request = context.getRequest ();
	switch (state_) {
		case COMPLETE:
			return true;
		case WAITINGFORSIZE:
			if (buffer.getNextLine (chunk)) {
				std::stringstream ss;
				ss << std::hex << chunk;
				ss >> expectsize;
				state_ = WAITINGFORDATA;
			}
			else if (buffer.size () > MAXLENGHTSIZECHUNK)
				return false;
		case WAITINGFORDATA:
			if (buffer.size () >= expectsize) {
				if (!buffer.getNextLine (chunk)) return false;
				request->getRequestBody ().addBytes (chunk);
				if (expectsize == 0)
					state_ = COMPLETE;
				else
					state_ = WAITINGFORSIZE;
			}

	}
	return true;
}