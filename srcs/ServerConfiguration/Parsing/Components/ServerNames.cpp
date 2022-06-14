#include "ServerNames.hpp"

ServerNames::ServerNames (): SimpleComponent ("server_name") {}
ServerNames::ServerNames (const ServerNames& _rhs):SimpleComponent (_rhs), names (_rhs.names) {}
ServerNames& ServerNames::operator = (const ServerNames& _rhs) {
	if (this != &_rhs)
		names = _rhs.names;
	return *this;
}

ServerNames::~ServerNames () {}
bool ServerNames::isSet () const { return !names.empty (); }
void ServerNames::parse (Tokenizer& tokenizer) {
	std::pair<std::set<std::string>::iterator,bool> ret;
	while (tokenizer && !(*(tokenizer)).is_directive ()) {
		ret = names.insert (tokenizer.id ());
		if (ret.second == false)
			throw Error (tokenizer.error ("Server Names with same name"));
		++tokenizer;
	}
}
void ServerNames::print () const {
	for (std::set <std::string>::iterator it = names.begin (); it != names.end (); ++it) {
		std::cout << *it << " ";
	}
}

