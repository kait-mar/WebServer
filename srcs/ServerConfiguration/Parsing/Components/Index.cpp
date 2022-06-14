#include "Index.hpp"

Index::Index (): SimpleComponent ("index") {}
Index::Index (const Index& _rhs): SimpleComponent (_rhs), indexes (_rhs.indexes) {}
Index& Index::operator= (const Index& _rhs) {
	if (this != &_rhs)
		indexes = _rhs.indexes;
	return *this;
}
Index::~Index () {}
bool Index::isSet () const { return !indexes.empty (); }


void Index::parse (Tokenizer & tokenizer) {
	while (!(*(tokenizer)).is_directive ()) {
		indexes.push_back ((*tokenizer).id ());
		++tokenizer;
	}
}
void Index::print () const {
	for (std::vector<std::string>::const_iterator it = indexes.begin (); it != indexes.cend(); ++it) {
		std::cout << *it << " ";
	}
}
