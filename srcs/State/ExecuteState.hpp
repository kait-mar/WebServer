#ifndef __EXECUTE_STATE_HPP__
#define __EXECUTE_STATE_HPP__

#include "State.hpp"
#include "../Response/ResponseFiller.hpp"

class ExecuteState: public State {
	public:
		ExecuteState ();
		void handle ();
};

#endif