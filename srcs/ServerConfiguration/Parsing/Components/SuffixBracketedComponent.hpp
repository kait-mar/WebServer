#ifndef __SUFFIX_BRACKETED_COMPONENT_HPP__
#define __SUFFIX_BRACKETED_COMPONENT_HPP__

#include "Component.hpp"

class SuffixBracketedComponent: public Component {
	protected:
		std::string		_suf;
	public:
		SuffixBracketedComponent (const std::string &, bool sin, unsigned _sub);
		SuffixBracketedComponent (const SuffixBracketedComponent &);
		SuffixBracketedComponent& operator = (const SuffixBracketedComponent&);
		~SuffixBracketedComponent ();
		std::string&	_suffix ();
		Component*clone () const {
			return new SuffixBracketedComponent (*this);
		}
		void pretty_print (std::string _tab = "") const;
		void syntax_parse (Tokenizer &);
		std::string	get_suf() const {	return _suf;}

};

typedef SuffixBracketedComponent Location;

#endif