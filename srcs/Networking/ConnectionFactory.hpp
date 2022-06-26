#ifndef __CONNECTION_FACTORY_HPP__
#define __CONNECTION_FACTORY_HPP__

class Connection;
class ConnectionsHandler;

class ConnectionFactory {
	protected:
		ConnectionsHandler *handler;
	public:
		void setHandler (ConnectionsHandler *);
		virtual Connection *create (int fd) const = 0;
	protected:
		bool setNonBlocking (int fd) const;
};

struct DataConnectionFactory: ConnectionFactory {
	Connection *create (int fd) const;
};

struct ListenConnectionFactory: ConnectionFactory {
	Connection *create (int fd) const;
};

#endif