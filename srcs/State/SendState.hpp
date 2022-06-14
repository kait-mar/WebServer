#ifndef __SEND_STATE_HPP__
#define __SEND_STATE_HPP__

#include "State.hpp"

class SendState: public State {
	private:
		void CloseAfter (bool);
	public:
		SendState (bool close = true);
		bool	closeAfterSend;
		void handle ();
};


#endif