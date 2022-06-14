#ifndef __LISTEN_CONNECTION_HPP__
#define __LISTEN_CONNECTION_HPP__


#include <map>
#include <vector>
#include "Connection.hpp"

class ConnectionsHandler;
/************************************************
 * connection that accepts other dataConnections 
 * *********************************************/

class ListenConnection: public Connection {
    private:
		ConnectionsHandler *handler;
	public:
        ListenConnection (int fd, ConnectionsHandler *);
        ~ListenConnection ();
		bool getClose ();
		void handle ();
};

#endif