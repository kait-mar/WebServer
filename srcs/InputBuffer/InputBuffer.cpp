#include "InputBuffer.hpp"

#include <unistd.h>
#include <iostream>

InputBuffer::InputBuffer () {}
InputBuffer::~InputBuffer () {}

bool 	InputBuffer::read (int fd) {
	char	*buff = new char [1024];

	ssize_t	rd = ::read (fd, buff, 1024);
	if (rd <= 0) {
		delete [] buff;
		return false;
	}
	buffer.append (buff, buff + rd);
	delete [] buff;
	return true;
}

bool	InputBuffer::getNextLine (std::string& line) {
	std::string::size_type n = buffer.find ("\r\n");
	if (n != std::string::npos) {
		line = buffer.substr (0, n);
		buffer.assign (buffer.begin () + n + 2, buffer.end ());
		return true;
	}
	return false;
}

std::string* InputBuffer::getPart (size_t size) {
	if (size > this->size ())
		return 0x0;
	else {
		std::string *buff = new std::string ();
		*buff = buffer.substr (0, size);
		buffer.assign (buffer.begin () + size, buffer.end ());
		return buff;
	}
}

size_t InputBuffer::size () const {
	return buffer.size ();
}

void InputBuffer::print () {
	std::cout << buffer << std::endl;
}