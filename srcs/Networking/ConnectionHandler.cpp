#include "ConnectionHandler.hpp"

#include <set>

#include "Connections/DataConnection.hpp"
#include "Sockets/socket.hpp"
#include "../ServerConfiguration/Configuration.hpp"
#include "Multiplexer/PollMultiplexer.hpp"
#include "Multiplexer/SelectMultiplexer.hpp"

ConnectionsHandler::ConnectionsHandler () {
	ListenConFactory.setHandler (this);
	DataConFactory.setHandler (this);
	Monitor = new SelectMultiplexer ();
}

bool ConnectionsHandler::setUp () {
    std::set<std::pair<u_int32_t, u_int16_t> > listens;
	std::vector<Server *> Vservers (Configuration::instance ()->getConfigurations ()->getSubComponents_<Server> ());
	for (std::vector<Server *>::iterator it = Vservers.begin (); it != Vservers.end (); ++it) {
		Listen		*listen = (*it)->getSimpleAttribute_ <Listen> ();
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
