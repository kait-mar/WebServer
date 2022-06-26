#include "ConnectionHandler.hpp"

#include <set>

#include "Connections/DataConnection.hpp"
#include "Sockets/socket.hpp"
#include "../ServerConfiguration/Configuration.hpp"
#include "Multiplexer/PollMultiplexer.hpp"

ConnectionsHandler::ConnectionsHandler () {
	ListenConFactory.setHandler (this);
	DataConFactory.setHandler (this);
	Monitor = new PollMultiplexer ();
}

bool ConnectionsHandler::setUp () {
    std::set<std::pair<u_int32_t, u_int16_t> > listens;
	std::vector<Server *> Vservers (Configuration::instance ()->getConfigurations ()->getSubComponents_<Server> ());

	std::set<std::pair<u_int16_t, std::string> > listServeNames;
	for (std::vector<Server *>::iterator it = Vservers.begin (); it != Vservers.end (); ++it) {
		ServerNames *servername = (*it)->getSimpleAttribute_ <ServerNames> ();
		Listen *listen = (*it)->getSimpleAttribute_ <Listen> ();
		if (servername) {
			std::set<std::string> names = servername->getNames ();
			for (std::set<std::string>::const_iterator it = names.cbegin (); it != names.cend (); ++it) {
				if (listServeNames.insert (std::make_pair(listen->getPort (), *it)).second == false) {
					Configuration::instance ()->getLogger().ErrorLog ("multiple servers with same servernames and port\n");
					return false;
				}
			}
		}
	}
	for (std::vector<Server *>::iterator it = Vservers.begin (); it != Vservers.end (); ++it) {
		Listen		*listen = (*it)->getSimpleAttribute_ <Listen> ();
		std::pair<u_int32_t, u_int16_t> lstn (listen->getAddress (), listen->getPort ());
		listens.insert (std::make_pair (listen->getAddress (), listen->getPort ()));
	}
	for (std::set<std::pair<u_int32_t, u_int16_t> >::const_iterator it = listens.begin (); it != listens.end (); ++it) {
		Addr 			addr ((*it).second, (*it).first);
		ListenSocket	sock;
		if (sock.getFd () >= 0 && sock.bind (addr)) {
			Connection * connection = ListenConFactory.create (sock.getFd ());
			if (connection)
				Monitor->Register (connection);
		}
		else {
			Configuration::instance ()->getLogger().ErrorLog ("error in creating Listen Connections\n");
			return false;
		}
	}
	return true;
}

void ConnectionsHandler::start () {
	if (this->setUp ()) {
		for (;;) {
			if (Monitor->Monitor ()) {
				Monitor->First ();
				while (!Monitor->isDone ()) {
					Connection *connection = Monitor->Current ();
					if (connection->getClose ())
						Monitor->Unregister (connection);
					else
						connection->handle ();
					Monitor->Next ();
				}
			}
			else if (Monitor->change ()) {
				Multiplexer *multiplexer = new PollMultiplexer (*(this->Monitor));
				Configuration::instance ()->getLogger ().ErrorLog ("changing Multiplexer");
				delete Monitor;
				this->Monitor = multiplexer;
			}
		}
	}
}
