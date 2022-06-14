#include "BracketedComponent.hpp"

#include "../ComponentFactory/ComponentCreator.hpp"

BracketedComponent::BracketedComponent (const std::string& _dir, bool sin, unsigned _sub): Component (_dir, sin, _sub) {}
BracketedComponent::BracketedComponent (const BracketedComponent& _rhs): Component (_rhs) {}
BracketedComponent& BracketedComponent::operator = (const BracketedComponent& _rhs) {
	if (this != &_rhs)
		Component::operator= (_rhs);
	return *this;
}
BracketedComponent::~BracketedComponent () {}
void BracketedComponent::pretty_print (std::string _tab) const {
	if (isSet ()) {
		std::cout << _tab << _dir << " {\n";
		for (std::map<std::string, Component *>::const_iterator it = _subComp.begin (); it != _subComp.end (); ++it)
			(*it).second->pretty_print (_tab + "\t");
		std::cout << _tab << "}\n";
	}
}
void BracketedComponent::syntax_parse (Tokenizer& tokenizer) {
	tokenizer.expect (_dir);
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