#include "PollMultiplexer.hpp"

#include "../Connections/ListenConnection.hpp"

PollMultiplexer::PollMultiplexer (const Multiplexer& rhs): Multiplexer (rhs) {}

bool PollMultiplexer::change () const  {
	return false;
}

bool PollMultiplexer::Monitor () {
	for (std::vector<Connection *>::iterator iter = this->pendings.begin (); iter != this->pendings.end (); ++iter)
		screen.insert (std::make_pair ((*iter)->getFd (), *iter));
	pendings.clear ();
	pollfds.clear ();
	for (std::map<int, Connection *>::iterator iter = screen.begin (); iter != screen.end (); ++iter) {
		pollfd p;
		p.fd = iter->first;
		if (dynamic_cast<ListenConnection *> (iter->second)) {
			p.events = READ;
		}
		else {
			p.events = READ | WRITE;
		}
		pollfds.push_back (p);
	}
	int ret = ::poll (&(pollfds[0]), pollfds.size (), -1);
	if (ret < 0) return false;
	for (std::vector<pollfd>::iterator iter = pollfds.begin (); iter != pollfds.end (); ++iter)
		screen.find (iter->fd)->second->setEvent (iter->revents);
	return true;
}