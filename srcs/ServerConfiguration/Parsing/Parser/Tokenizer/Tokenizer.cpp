#include "Tokenizer.hpp"

Error::Error (const std::string& _error): error (_error) {}

const char* Error::what () const _NOEXCEPT { return error.c_str (); }

Tokenizer::Tokenizer (std::ifstream& s): is (s) {
	this->tokenize ();
} 

void Tokenizer::add_token (std::string& tkn, unsigned int line, unsigned int column) {
	if (!tkn.empty ()) {
		Token token (tkn, line, column - tkn.size ());
		if (!tokens.empty ()) {
			std::string last = tokens.back ().id ();
			if ((last == ";" && tkn == ";") ||
				(last == "{" && tkn == "{") ||
				(last == "{" && tkn == ";") ||
				(last == "{" && tkn == "}") ||
				(last == "}" && tkn == ";")) {
				throw Error (token.status("unexpected token"));
			}
		}
		tokens.push_back (token);
		tkn.clear ();
	}
}

void Tokenizer::tokenize () {
	unsigned int line = 1;
	unsigned int column = 1;
	typedef std::istream_iterator <char> streamer;
	std::noskipws (is);
	std::string token;
	for (streamer it = is; it != streamer (); ++it, ++column) {
		switch (*it) {
			case '#':
				while ((it != streamer () && *it != '\n'))
					++it;
			case '\n':
				add_token (token, line, column);
				line++;
				column = 0;
				break;
			case ';':
			case '}':
			case '{':
				add_token (token, line, column);
				token += *it;
				add_token (token, line, column + 1);
				break;
			default:
				if (isspace (*it)) {
					add_token (token, line, column);
					if (*it == '\t') column += 3;
					break;
				}
				token += *it;
		}
	}
	add_token (token, line, column);
	current = tokens.cbegin ();
}

const Token& Tokenizer::operator *() const { return *current; }

Tokenizer& Tokenizer::operator++ () { ++current; return *this; }

void Tokenizer::expect (const std::string& directive) {
	if (current == tokens.end ())
		throw std::runtime_error (directive + " is missing at end of file ");
	(*current).expect (directive);
	++current;
}

Tokenizer::operator bool ()  { return current != tokens.cend (); }

std::string Tokenizer::error (const char *error) const {
	return (*current).status (error);
}

const std::string& Tokenizer::id () const {
	return (*current).id ();
}