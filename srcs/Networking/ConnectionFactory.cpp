#include "ConnectionFactory.hpp"

#include "Connections/ListenConnection.hpp"
#include "Connections/DataConnection.hpp"
#include "ConnectionHandler.hpp"

void ConnectionFactory::setHandler (ConnectionsHandler *_handler) {
	handler = _handler;
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
