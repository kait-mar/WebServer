#include "ErrorPages.hpp"

ErrorPages::ErrorPages (): SimpleComponent ("error_page", false) {}
ErrorPages::ErrorPages (const ErrorPages& _rhs):SimpleComponent (_rhs), error_pages (_rhs.error_pages) {}
ErrorPages& ErrorPages::operator = (const ErrorPages& _rhs) {
	if (this != &_rhs)
		error_pages = _rhs.error_pages;
	return *this;
}

ErrorPages::~ErrorPages () {}


bool ErrorPages::isSet () const { return !error_pages.empty (); }
void ErrorPages::parse (Tokenizer& tokenizer) {
	std::pair <std::map<unsigned short, std::string>::iterator, bool> ret;
	while (!(*tokenizer).is_directive ()) {
		unsigned short		code;
		std::string			scode;
		std::string			path;
		std::string token = (*tokenizer).id ();
		if (token.find (":") == std::string::npos)
			throw Error (tokenizer.error ("expecting XXX:/yyy/yy"));
		scode = token.substr (0, token.find (':'));
		path = token.substr (token.find (':') + 1);
		if (all_of_ (scode.begin (), scode.end (), is_digit ())) {
			code = atoi (scode.c_str ());
			if (code <= 0xFFFF) {
				if (!path.empty ()) {
					if (error_pages.insert (std::make_pair (code, path)).second == false)
						throw Error (tokenizer.error ("error page already set"));
				}
				else
					throw Error (tokenizer.error ("empty path"));
			}
			else
				throw Error (tokenizer.error ("code out of range"));
		}
		else
			throw Error (tokenizer.error ("expected a code"));
		++tokenizer;
	}
}
void ErrorPages::print () const {
	for (std::map <unsigned short, std::string>::const_iterator it = error_pages.cbegin (); it != error_pages.end (); ++it) {
		std::cout << it->first << ":" << it->second << " ";
	}
}

std::map <unsigned short, std::string>	&ErrorPages::getErrorPages()
{
	return error_pages;
}
