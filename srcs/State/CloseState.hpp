#ifndef __CLOSE_STATE_HPP__
#define __CLOSE_STATE_HPP__

#include "State.hpp"

class CloseState: public State {
	public:
		CloseState ();
		void handle ();
};

#endif
