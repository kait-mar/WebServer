#include "Upload.hpp"

Upload::Upload (): SimpleComponent ("upload") {}
Upload::Upload (const Upload& _rhs): SimpleComponent (_rhs), root (_rhs.root) {}
Upload& Upload::operator= (const Upload& _rhs) {
	if (this != &_rhs)
		root = _rhs.root;
	return *this;
}
Upload::~Upload () {}
bool Upload::isSet () const { return !root.empty (); }


void Upload::parse (Tokenizer &tokenizer) {
	root = (*tokenizer).id ();
	++tokenizer;
}
void Upload::print () const {
	std::cout << root;
}