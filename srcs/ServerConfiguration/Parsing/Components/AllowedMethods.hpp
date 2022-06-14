#ifndef __ALLOWED_METHODS_HPP__
#define __ALLOWED_METHODS_HPP__

#include <set>
#include <array>
#include "SimpleCompoent.hpp"

static const std::array<const char *, 3> supportedMethods = {"GET", "POST", "DELETE"};

class AllowedMethods: public SimpleComponent {
	private:
		std::set <std::string> methods;
	public:
		AllowedMethods ();
		AllowedMethods (bool);
		AllowedMethods (const AllowedMethods&);
		AllowedMethods& operator = (const AllowedMethods& );
		~AllowedMethods ();
		Component *clone () const {
			return new AllowedMethods (*this);
		}
		void print (void) const;
		bool isSet () const;
		void parse (Tokenizer& );
		std::set <std::string>	&getMethods();
};

#endif