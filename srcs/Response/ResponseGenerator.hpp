#ifndef __RESPONSE_GENERATOR_HPP__
#define __RESPONSE_GENERATOR_HPP__


#include "Response.hpp"

class	Response;

class ResponseGenerator {
	protected:
		Response *response;
	public:
		ResponseGenerator ();
		Response* getResponse ();
		virtual ~ResponseGenerator ();
		void build () {
			this->add_response_line ();
			this->add_header_fields ();
			this->add_payload ();
		}
		virtual void add_response_line () = 0;
		virtual void add_header_fields () = 0;
		virtual void add_payload () {};
};

class ErrorGenerator: public ResponseGenerator {
	private:
		unsigned short code;
		const char *path;
	public:
		ErrorGenerator (unsigned short, const char * = 0x0);
		~ErrorGenerator () {};
		void add_response_line ();
		void add_header_fields ();
		void add_payload ();
};

#endif