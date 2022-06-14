#ifndef __SIMPLE_COMPONENT_HPP__
#define __SIMPLE_COMPONENT_HPP__


#include "Component.hpp"

class SimpleComponent: public Component {
	public:
		SimpleComponent (const std::string &, bool sin = true);
		SimpleComponent (const SimpleComponent &);
		SimpleComponent& operator = (const SimpleComponent&);
		virtual ~SimpleComponent ();
		virtual void print (void) const = 0;
		virtual void parse (Tokenizer& ) = 0;
		virtual void pretty_print (std::string _tab = "") const;
		virtual void syntax_parse (Tokenizer &);
};

#endif