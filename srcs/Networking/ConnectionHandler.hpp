#ifndef __CONNECTIONHANDLER_HPP_
#define __CONNECTIONHANDLER_HPP_

#include <vector>
#include <map>

#include "ConnectionFactory.hpp"
#include "Connections/DataConnection.hpp"
#include "Connections/ListenConnection.hpp"

#include "Multiplexer/Multiplexer.hpp"




/************************************************
 * handle the connection events using poll API
 * the main function will call start () after
 * the parsing the configuation file
 * **********************************************/

class ConnectionsHandler {
	private:
		ListenConnectionFactory ListenConFactory;
		DataConnectionFactory 	DataConFactory;
		Multiplexer *Monitor;
		friend class ListenConnection;
		bool setUp ();
	public:
		void setMultiplexer (Multiplexer *);
		ConnectionsHandler ();
		void start ();
};



#endif