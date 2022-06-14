#ifndef __REQUEST_LINE_HPP__
#define __REQUEST_LINE_HPP__

#include <string>
#include <vector>
#include <iostream>
#include "../utility/utility.hpp"
#include "Uri.hpp"

class RequestLine {
	private:
		std::string		method;
		URI				URL;
		std::string		httpversion;
		bool			isparsed;
		std::vector<std::string>    split(std::string, std::string); /*utility*/
	public:
		RequestLine ();
		~RequestLine ();
		
		void setMethod (const std::string& m);
		const std::string& getMethod () const;
		
		const URI& getURL () const;
		URI& getURL () ;
		void setURL (const std::string& url);
		const std::string& getVersion () const;
		void setVersion (const std::string& v);
		
		bool isParsed () const;
		bool parse (const std::string&);
		void clear ();
		void print () const;
};


#endif