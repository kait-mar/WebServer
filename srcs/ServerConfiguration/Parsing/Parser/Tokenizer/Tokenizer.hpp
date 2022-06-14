#ifndef __TOKENIZER_HPP_
#define __TOKENIZER_HPP_

#include <exception>
#include <vector>
#include <fstream>

#include "Tokens.hpp"

struct Error: public std::exception  {
	std::string error;
	Error (const std::string& _error);
	~Error () _NOEXCEPT {}
	virtual const char *what () const _NOEXCEPT;
};

class Tokenizer {
	private:
		std::vector <const Token> tokens;
		std::ifstream&	is;
		std::vector<const Token>::const_iterator current;
		void add_token (std::string&, unsigned int, unsigned int);
		void tokenize ();
	public:
		Tokenizer (std::ifstream&);
		std::string error (const char *error) const;
		const std::string& id () const;
		void expect (const std::string& id);
		const Token& operator *() const;
		Tokenizer& operator++ ();
		operator bool ();
};

#endif