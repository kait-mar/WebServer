#include "Root.hpp"

Root::Root (): SimpleComponent ("root") {}
Root::Root (const Root& _rhs): SimpleComponent (_rhs), root (_rhs.root) {}
Root& Root::operator= (const Root& _rhs) {
	if (this != &_rhs) 
		root = _rhs.root;
	return *this;
}
Root::~Root () {}
bool Root::isSet () const { return !root.empty (); }
void Root::parse (Tokenizer &tokenizer) {
	root = (*tokenizer).id ();
	++tokenizer;
}
void Root::print () const {
	std::cout << root;
}

