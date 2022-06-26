#ifndef __SERVER_NAMES_HPP__
#define __SERVER_NAMES_HPP__

#include "SimpleCompoent.hpp"

#include <set>

class ServerNames: public SimpleComponent {
	private:
		std::set <std::string>	names;
	public:
		ServerNames ();
		ServerNames (const ServerNames&);
		ServerNames& operator = (const ServerNames& );
		~ServerNames ();
		Component* clone () const {
			return new ServerNames (*this);
		}
		void print () const;
		bool isSet () const;
		bool empty () const;
		void parse (Tokenizer& );
		std::set <std::string>	&getNames()	{	return (names);	}
};

#endif