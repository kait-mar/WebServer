#ifndef __SELECT_MULTIPLEXER_HPP__
#define __SELECT_MULTIPLEXER_HPP__

#include "Multiplexer.hpp"
#include <sys/select.h>
#include <vector>

class SelectMultiplexer: public Multiplexer {
	private:
		fd_set		*readSet;
		fd_set		*writeSet;
		static const int MAX_FD_SET_SIZE = FD_SETSIZE;
		bool ch;
	public:
		SelectMultiplexer ();
		~SelectMultiplexer ();
		bool change () const;
		bool Monitor ();
};


#endif