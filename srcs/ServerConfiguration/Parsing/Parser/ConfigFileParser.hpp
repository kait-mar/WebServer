#ifndef __CONFIG_FILE_PARSER_HPP__
#define __CONFIG_FILE_PARSER_HPP__

#include "Tokenizer/Tokenizer.hpp"
#include "../ComponentFactory/ComponentCreator.hpp"


class ConfigFileParser {
	private:
		std::string path;
		void format (Component *) const;
	public:
		ConfigFileParser (const char *);
		Component *parse () const;		
};

#endif