#ifndef __PAYLOAD_STATE_HPP__
#define __PAYLOAD_STATE_HPP__

#include "State.hpp"

enum TRANSFERTYPE {
					RAW,
					CHUNKED,
				};

class TransferEncoding;

class PayloadState: public State {
	private:
		unsigned int lenght;
		TransferEncoding *encoding;
		TRANSFERTYPE type;
	public:
		PayloadState (TRANSFERTYPE _type, unsigned int lenght = 0);
		~PayloadState ();
		void handle ();
};

#endif