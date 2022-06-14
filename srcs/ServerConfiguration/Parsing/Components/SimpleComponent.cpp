#include "SimpleCompoent.hpp"

SimpleComponent::SimpleComponent (const std::string& _dir, bool sin): Component (_dir, sin) {}
SimpleComponent::SimpleComponent (const SimpleComponent& _rhs): Component (_rhs) {}
SimpleComponent& SimpleComponent::operator = (const SimpleComponent& _rhs) {
	if (this != &_rhs) 
		Component::operator= (_rhs);
	return *this;
}

SimpleComponent::~SimpleComponent () {}
void SimpleComponent::pretty_print (std::string _tab) const {
	if (isSet ()) {
		std::cout << _tab << _dir << " ";
		print ();
		std::cout << ";\n";
	}
}
void SimpleComponent::syntax_parse (Tokenizer &tokenizer) {
	tokenizer.expect (_dir);
	parse (tokenizer);
	if (!isSet ()) throw Error (tokenizer.error ("empty directive"));
	tokenizer.expect (";");
}