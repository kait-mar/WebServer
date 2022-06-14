#include "SuffixBracketedComponent.hpp"

#include "../ComponentFactory/ComponentCreator.hpp"

SuffixBracketedComponent::SuffixBracketedComponent (const std::string& _dir, bool sin, unsigned _sub): Component (_dir, sin, _sub) {}
SuffixBracketedComponent::SuffixBracketedComponent (const SuffixBracketedComponent& _rhs): Component (_rhs), _suf (_rhs._suf) {}
SuffixBracketedComponent& SuffixBracketedComponent::operator = (const SuffixBracketedComponent& _rhs) {
	if (this != &_rhs) {
		Component::operator= (_rhs);
		_suf = _rhs._suf;
	}
	return *this;
}
SuffixBracketedComponent::~SuffixBracketedComponent () {}
std::string& SuffixBracketedComponent::_suffix () { return _suf; }
void SuffixBracketedComponent::pretty_print (std::string _tab) const {
	if (isSet ()) {
		std::cout << _tab << _dir << " " << _suf << " {\n";
		for (std::map<std::string, Component *>::const_iterator it = _subComp.begin (); it != _subComp.end (); ++it)
			(*it).second->pretty_print (_tab + "\t");
		std::cout << _tab << "}\n";
	}
}
void SuffixBracketedComponent::syntax_parse (Tokenizer& tokenizer) {
	tokenizer.expect (_dir);
	_suf = (*tokenizer).id ();
	++tokenizer;
	tokenizer.expect ("{");
	while (tokenizer && (*tokenizer).id () != "}") {
		std::string id = tokenizer.id ();
		if (isSub (id)) {
			std::multimap <std::string, Component *>::iterator it = _subComp.find (id);
			if (it != _subComp.end ()) {
				if (((*it).second)->sin ())
					throw Error (tokenizer.error ("only one component allowed"));
			}
			Component * comp = ComponentCreator::instance ()->create (id);
			comp->syntax_parse (tokenizer);
			_subComp.insert (std::make_pair (id, comp));
		}
		else
			throw Error (tokenizer.error ("not a sub component"));
	}
	tokenizer.expect ("}");
}