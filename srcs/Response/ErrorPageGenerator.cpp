#include "ErrorPageGenerator.hpp"

#include <stdio.h>
#include "../ServerConfiguration/Configuration.hpp"


std::string ErrorPageGenerator (unsigned short _code) {
	char buff[256];

	::sprintf (buff, templte, _code, Configuration::codeToReasonPhrase (_code).c_str ());
	return buff;
};
