#ifndef __STATE_HPP__
#define __STATE_HPP__


#include "../Networking/Connections/DataConnection.hpp"

class State {
	protected:
		dataConnection	*context;
    public:
		virtual ~State () {}; 
        virtual void handle () = 0;
		void setContext (dataConnection *_context) {
			this->context = _context;
		}
};

#endif