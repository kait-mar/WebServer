#ifndef __ERROR_PAGES_HPP__
#define __ERROR_PAGES_HPP__

#include "SimpleCompoent.hpp"

class ErrorPages: public SimpleComponent {
	private:
		std::map <unsigned short, std::string> error_pages;
	public:
		ErrorPages ();
		ErrorPages (const ErrorPages&);
		ErrorPages& operator = (const ErrorPages& );
		~ErrorPages ();
		Component* clone () const {
			return new ErrorPages (*this);
		};
		bool isSet () const;
		void print () const;
		void parse (Tokenizer& );
		std::map <unsigned short, std::string>	&getErrorPages();
};


#endif