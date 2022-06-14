#include "Connection.hpp"

#include <unistd.h>

Connection::Connection (int _fd): fd (_fd) {}
Connection::~Connection () {
	this->close ();
}

int	Connection::getFd () const { return fd; }

void	Connection::close () { ::close (fd); }

void Connection::setEvent (Event e) {
	event = e;
}

const Event& Connection::getEvent () const {
	return event;
}
