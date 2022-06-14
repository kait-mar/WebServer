#include "AllowedMethods.hpp"

#include "../Parser/Tokenizer/Tokenizer.hpp"


AllowedMethods::AllowedMethods (): SimpleComponent ("allowed_methods") {}
AllowedMethods::AllowedMethods(bool fill):SimpleComponent ("allowed_methods") {
	if (fill) {
		this->methods.insert ("GET");
		this->methods.insert ("POST");
	}
}

AllowedMethods::~AllowedMethods () {}
AllowedMethods::AllowedMethods (const AllowedMethods& _rhs): SimpleComponent (_rhs), methods (_rhs.methods) {}
AllowedMethods& AllowedMethods::operator = (const AllowedMethods& _rhs) {
	if (this != &_rhs)
		methods = _rhs.methods;
	return *this;
}
bool AllowedMethods::isSet () const { return !methods.empty (); }


void AllowedMethods::parse (Tokenizer& tokenizer) {
	std::pair<std::set<std::string>::iterator,bool> ret;
	while (!(*tokenizer).is_directive ()) {
		std::string tmp = tokenizer.id ();
		std::transform (tmp.begin (), tmp.end (), tmp.begin (), ::toupper);
		bool found = false;
		for (std::array<const char *, 3>::const_iterator iter = supportedMethods.cbegin (); iter != supportedMethods.cend (); ++iter) {
			if (tmp == *iter) {
				found = true;
				break;
			};
		}
		if (!found)
			throw Error (tokenizer.error ("Unknown Method"));
		ret = methods.insert (tmp);
		if (ret.second == false)
			throw Error (tokenizer.error ("multiple methods with same name"));
		++tokenizer;
	}
}
void AllowedMethods::print () const {
	for (std::set <std::string>::iterator it = methods.begin (); it != methods.end (); ++it) {
		std::cout << *it << " ";
	}
}


std::set <std::string>	&AllowedMethods::getMethods()	{	return methods;	}
