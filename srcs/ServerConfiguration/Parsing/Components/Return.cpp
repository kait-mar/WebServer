#include "Return.hpp"

Return::Return (): SimpleComponent ("return"), is_set (false) {}
Return::Return (const Return& _rhs): SimpleComponent (_rhs) {
	code = _rhs.code;
	_code = _rhs._code;
	path = _rhs.path;
}
Return& Return::operator= (const Return& _rhs) {
	if (this != &_rhs) {
		code = _rhs.code;
		_code = _rhs._code;
		path = _rhs.path;
	}
	return *this;
}
Return::~Return () {}


bool Return::isSet () const { return is_set; }

void Return::parse (Tokenizer& tokenizer) {
	if (!(*tokenizer).is_directive ()) {
		_code = (*tokenizer).id ();
		code = atoi (_code.c_str ());
		if (code <= 0xFFFF) {
			++tokenizer;
			if (!(*tokenizer).is_directive ()) {
				path = (*tokenizer).id ();
				++tokenizer;
				is_set = true;
				return;
			}
			else
				throw Error (tokenizer.error ("expecting a path"));
		}
		else
			throw Error (tokenizer.error ("code out of range"));
	}
	else
		throw Error (tokenizer.error ("expecting a code"));
}

void Return::print () const {
	std::cout << _code << " " << path;
}

unsigned short Return::getCode () const { 
	return code;
}
std::string Return::getPath () const {
	return path;
}