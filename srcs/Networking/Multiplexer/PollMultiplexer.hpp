#ifndef __POLL_MULTIPLEXER_HPP__
#define __POLL_MULTIPLEXER_HPP__

#include "Multiplexer.hpp"
#include "poll.h"
#include <vector>

class PollMultiplexer: public Multiplexer {
	private:
		std::vector<pollfd> pollfds;
	public:
		PollMultiplexer () {}
		PollMultiplexer (const Multiplexer&);
		bool change () const;
		bool Monitor ();
};

#endif