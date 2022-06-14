#ifndef __ERROR_STATE_HPP__
#define __ERROR_STATE_HPP__

#include "State.hpp"

class ErrorState: public State {
	private:
		unsigned short _code;
		const char		*path;
	public:
		ErrorState (unsigned short code, const char * = 0x0);
		void handle ();
};

#endif