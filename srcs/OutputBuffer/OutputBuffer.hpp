#ifndef __OUTPUT_BUFFER_HPP__
#define __OUTPUT_BUFFER_HPP__

#include "../Response/Response.hpp"

class Response;

class OutputBuffer {
	private:
		int fd;
		std::string	 output;
		size_t		index;
		bool 		sent;
	public:
		OutputBuffer (int fd);
		void setResponseToSend (Response&);
		bool isSent () const;
		bool send ();
};
#endif