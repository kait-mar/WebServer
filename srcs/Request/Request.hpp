#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "HeaderFields.hpp"
#include "RequestLine.hpp"
#include "../Response/Payload.hpp"

class Request {
	private:
		RequestLine		*requestline;
		HeaderFields	*hf;
		Payload			*pl;
	public:
		Request ();
		~Request ();
		bool isParsed () const;
		bool parse (const std::string&);
		void clear ();
		void print () const;
		RequestLine *get_requestLine();
		HeaderFields *get_headerFields();
		const HeaderFields&	getHeaderFields() const;
		HeaderFields&	getHeaderFields();
		const RequestLine&	getRequestLine() const;
		RequestLine			&getRequestLine();
		const Payload& getRequestBody () const;
		Payload& getRequestBody ();
};

#endif