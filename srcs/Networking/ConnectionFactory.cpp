#include "ConnectionFactory.hpp"

#include "fcntl.h"

#include "Connections/ListenConnection.hpp"
#include "Connections/DataConnection.hpp"
#include "ConnectionHandler.hpp"

void ConnectionFactory::setHandler (ConnectionsHandler *_handler) {
	handler = _handler;
}

bool ConnectionFactory::setNonBlocking(int fd) const {
	int flags = fcntl (fd, F_GETFL);
	flags |= O_NONBLOCK;
	return (fcntl (fd, F_SETFL, flags) != -1);
}

Connection *DataConnectionFactory::create (int fd) const {
	Connection *connection = new dataConnection (fd);
	connection->setEvent (READ | WRITE);
	return connection;
}


Connection *ListenConnectionFactory::create (int fd) const {
	Connection *connection = new ListenConnection (fd, this->handler);
	connection->setEvent (READ);
	return connection;
}
