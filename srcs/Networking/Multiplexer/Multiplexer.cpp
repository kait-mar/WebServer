#include "Multiplexer.hpp"

Multiplexer::Multiplexer () {
	iter = this->screen.begin ();
}

Multiplexer::Multiplexer (const Multiplexer& rhs): screen (rhs.screen), pendings (rhs.pendings) {
	iter = rhs.iter;
}

void Multiplexer::Register (Connection *connection) {
	this->pendings.push_back (connection);
}

void Multiplexer::First () {
	iter = screen.begin ();
}

void Multiplexer::Next () {
	if (iter != screen.end ())
		++iter;
}

Connection *Multiplexer::Current () const {
	return iter->second;
}


void Multiplexer::Unregister (Connection *connection) {
	if (iter->first == connection->getFd ()) {
		iter = screen.erase (iter);
		delete connection;
	}
}

bool Multiplexer::isDone () const {
	return (iter == screen.end ());
}
