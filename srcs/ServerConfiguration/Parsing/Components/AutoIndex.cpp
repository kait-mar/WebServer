#include "AutoIndex.hpp"

AutoIndex::AutoIndex (): SimpleComponent ("auto_index"), on ("") {}
AutoIndex::AutoIndex (const AutoIndex& _rhs): SimpleComponent (_rhs), on (_rhs.on) {}
AutoIndex& AutoIndex::operator = (const AutoIndex& _rhs) {
	if (this != &_rhs)
		on = _rhs.on;
	return *this;
}
AutoIndex::~AutoIndex () {}


bool AutoIndex::isSet () const { return !on.empty (); }
void AutoIndex::parse (Tokenizer& tokenizer) {
	if (tokenizer.id () == "on" || tokenizer.id () == "off") {
		on = (*tokenizer).id ();
		++tokenizer;
	}
	else
		throw Error (tokenizer.error ("expected on/off"));
}
void AutoIndex::print () const {
	std::cout << on;
}

std::string	&AutoIndex::getAutoIndex() {	return on;	}