#include "BodySize.hpp"

#include "utils.hpp"

#define MEGA 1024 * 1024

BodySize::BodySize (): SimpleComponent ("max_body_size"), size (0), already_set (false) {}
BodySize::BodySize (unsigned int size_): SimpleComponent ("max_body_size") {
	size = size_ * MEGA;
	already_set = true;
}

BodySize::BodySize (const BodySize& _rhs): SimpleComponent (_rhs), size (_rhs.size), already_set (_rhs.already_set) {}
BodySize& BodySize::operator = (const BodySize& _rhs) {
	if (this != &_rhs) {
		size = _rhs.size;
		already_set = _rhs.already_set;
	}
	return *this;
}
BodySize::~BodySize () {}
void BodySize::setBodySize (unsigned int sz) { size = sz; } 
unsigned int BodySize::getBodySize () const { return size; }


bool BodySize::isSet () const { return already_set; }
void BodySize::parse (Tokenizer& tokenizer) {
	std::string sz = tokenizer.id ();
	if (sz.back() == 'M' && all_of_ (sz.begin (), sz.end () - 1, is_digit ())) {
		already_set = true;
		size = atoi (sz.substr(0, sz.size() - 1).c_str());
		if (size > 80)
			throw Error (tokenizer.error ("max_body_size is too large: accepted value below 50M"));
		size *= MEGA;
		++tokenizer;
	}
	else
		throw Error (tokenizer.error ("max body size format XXXM"));
}
void BodySize::print () const {
	std::cout << size;
}

