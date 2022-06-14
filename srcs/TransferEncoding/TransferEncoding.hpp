#ifndef __TRANSFER_ENCODING_HPP__
#define __TRANSFER_ENCODING_HPP__

#include "../Networking/Connections/DataConnection.hpp"

enum TRANSFERSTATE { 
					WAITINGFORSIZE,
					WAITINGFORDATA,
					COMPLETE
				};

class TransferEncoding {
	private:
		size_t		expectsize;
		TRANSFERSTATE state_;
	public:
		TransferEncoding ();
		bool isComplete () const;
		bool Decode (dataConnection& context);
};

#endif