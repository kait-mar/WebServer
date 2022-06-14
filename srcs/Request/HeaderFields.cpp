#include "HeaderFields.hpp"
#include <algorithm>
#include <ctype.h>
#include <exception>

HeaderFields::HeaderFields (): isparsed (false) {}

HeaderFields::~HeaderFields () {}


bool HeaderFields::isParsed () const {
	return isparsed;
}

void HeaderFields::clear () {
	isparsed = false;
	hf.clear ();
}

bool HeaderFields::parse (const std::string& input) {

	// if input is empty: the end of header fields
	if (input.size () == 0) {
		isparsed = true;
		return true;
	}
	
	// check if colon is present
	std::string::size_type colonpos = input.find_first_of (':');
	if (colonpos == std::string::npos) return false;

	// check if there is not WS in fieldname
	std::string field_name		= input.substr(0, colonpos);
	if (field_name.find_first_of ("\t ") != std::string::npos) return false;
	

	std::string field_value		= input.substr (colonpos + 1);
	
	// trim the field value from trailing and preceding WS
	size_t start = field_value.find_first_not_of ("\t ");
	if (start != std::string::npos)
		field_value = field_value.substr (start);
	
	size_t end	= field_value.find_last_not_of ("\t ");
	if (end != std::string::npos)
		field_value = field_value.substr (0, end + 1);
	
	hf[field_name] = field_value;
	return true;
}
 
void HeaderFields::print () const {
	for (headers::const_iterator it = hf.cbegin (); it != hf.end (); ++it) {
		std::cout << it->first << ":" << it->second << "\n";
	}
}

HeaderFields::headers HeaderFields::get_hf() {
	return hf;
}
bool HeaderFields::has (const std::string& name) const {
	return (hf.find (name) != hf.cend ());
}

const std::string& HeaderFields::operator [] (const std::string& name) const {
	if (!(this->has (name)))
		throw std::invalid_argument ("use has before []");
	return hf.find (name)->second;
}

void HeaderFields::remove (const std::string& name) {
	hf.erase (name);
}

void HeaderFields::add (const std::string& name, const std::string& value) {
	hf.insert (std::make_pair (name, value));
}

const std::string& HeaderFields::getHeader (const std::string& key)
{
	return hf[key];
}
