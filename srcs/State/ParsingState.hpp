#ifndef __PARSING_STATE_HPP__
#define __PARSING_STATE_HPP__

#include "State.hpp"
#include "../Request/RequestFilters/RequestFilters.hpp"

class ParsingState: public State {
	private:
		FiltersManager *filters;		
	public:
		ParsingState ();
		void handle ();
};

#endif