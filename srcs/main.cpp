#include <iostream>

#include "ServerConfiguration/Configuration.hpp"
#include "Networking/ConnectionHandler.hpp"

int main (int argc, char **argv) {
	(void)argc;

	ConfigFileParser Parser (argv[1]);

	Component *UserConf = Parser.parse ();
	if (!UserConf) return 1;
	Configuration::instance ()->setUSerConfig (UserConf);
//	UserConf->pretty_print ();
	ConnectionsHandler connection_handler;
	connection_handler.start ();

	return 1;
}
