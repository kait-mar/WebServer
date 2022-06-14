#include "SelectMultiplexer.hpp"

#include "../Connections/ListenConnection.hpp"

SelectMultiplexer::SelectMultiplexer () {
	readSet = new fd_set ();
	writeSet = new fd_set ();
	ch = false;
}

SelectMultiplexer::~SelectMultiplexer () {
	delete readSet;
	delete writeSet;
}

bool SelectMultiplexer::change () const {
	return ch;
}

bool SelectMultiplexer::Monitor () {
	if (this->screen.size () + this->pendings.size () > MAX_FD_SET_SIZE) {
		ch = true;
		return false;
	}
	for (std::vector<Connection *>::iterator iter = this->pendings.begin (); iter != this->pendings.end (); ++iter)
		screen.insert (std::make_pair ((*iter)->getFd (), *iter));
	pendings.clear ();
	FD_ZERO (readSet);
	FD_ZERO (writeSet);

	int max_fd = 0;
	for (std::map<int, Connection *>::iterator iter = screen.begin (); iter != screen.end (); ++iter) {
		int fd = iter->first;
		if (fd >= MAX_FD_SET_SIZE) {
			ch = true;
			return false;
		}
		max_fd = std::max (max_fd, fd);
		if (dynamic_cast<ListenConnection *> (iter->second)) {
			FD_SET (iter->first, readSet);
		}
		else {
			FD_SET (iter->first, readSet);
			FD_SET (iter->first, writeSet);
		}
	}
	timeval time = {};
	int ret = ::select (++max_fd, readSet, writeSet, nullptr, &time);
	if (ret < 0) return false;
	for (std::map<int, Connection*>::iterator iter = screen.begin (); iter != screen.end (); ++iter) {
		Event e;
		if (FD_ISSET (iter->first, readSet))
			e.set (READ);
		if (FD_ISSET (iter->first, writeSet))
			e.set (WRITE);
		iter->second->setEvent (e);
	}
	return true;
}

