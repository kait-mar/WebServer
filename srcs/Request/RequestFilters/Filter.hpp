#ifndef __FILTER_HPP__
#define __FILTER_HPP__

#include "../Request.hpp"

class Filter {
	private:
		unsigned short code; 
		virtual bool apply (const Request&) const = 0;   
	public:
		Filter (unsigned short code_): code (code_) {};
		virtual ~Filter () {};
		unsigned short filter (const Request& request) const {
			return (this->apply (request)) ? 0: code;
		}
};

#endif