#include "ListenConnection.hpp"

#include "DataConnection.hpp"
#include <poll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "../ConnectionHandler.hpp"

ListenConnection::ListenConnection (int fd, ConnectionsHandler *h): Connection (fd), handler (h) {}

ListenConnection::~ListenConnection () {}

void ListenConnection::handle () {
	if (this->getEvent () == READ) {
		do {
			int fd = ::accept (this->getFd (), 0x0, 0x0);
			if (fd < 0) break;
			Connection *connection = handler->DataConFactory.create (fd);
			if (connection)
				handler->Monitor->Register (connection);
		}while (1);
	}
}

bool ListenConnection::getClose () {
	return false;
}