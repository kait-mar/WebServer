#ifndef __BRACKETED_COMPONENT_HPP
#define __BRACKETED_COMPONENT_HPP

#include "Component.hpp"

class BracketedComponent: public Component {
	public:
		BracketedComponent (const std::string &, bool sin, unsigned _sub);
		BracketedComponent (const BracketedComponent &);
		BracketedComponent& operator = (const BracketedComponent&);
		~BracketedComponent ();
		Component *clone () const {
			return new BracketedComponent (*this);
		}
		void pretty_print (std::string _tab = "") const;
		void syntax_parse (Tokenizer &);
};

typedef BracketedComponent Server;

#endif