#include "OutputBuffer.hpp"

#include <unistd.h>

#include <iostream>
OutputBuffer::OutputBuffer (int _fd): fd (_fd), index (0), sent (false) {}

void OutputBuffer::setResponseToSend (Response& response) {
	output += response.getStatusLine ();
	output += response.getHeadersSection ();
	output += response.getPayload ().body ();
	index = 0;
	sent = false;
}
bool OutputBuffer::isSent () const  {
	return sent;
}

bool OutputBuffer::send () {
	if (index == output.size ()) {
		sent = true;
		output.clear ();
		return true;
	}
	ssize_t wr = ::write (this->fd, output.data () + index, output.size () - index);
	if (wr <= 0) return false;
	index += wr;
	return true;
}
