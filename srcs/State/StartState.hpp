#ifndef __START_STATE_HPP__
#define __START_STATE_HPP__

#include "State.hpp"

class StartState: public State {
	public:
		StartState ();
		void handle ();
};
#endif