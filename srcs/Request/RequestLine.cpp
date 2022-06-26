#include "RequestLine.hpp"

RequestLine::RequestLine (): isparsed (false) {}

RequestLine::~RequestLine () {}

void RequestLine::setMethod (const std::string& m) {
	method = m;
}

const std::string& RequestLine::getMethod () const {
	return method;
}

const URI& RequestLine::getURL () const {
	return URL;
}

URI& RequestLine::getURL () {
	return URL;
}

void RequestLine::setURL (const std::string& url) {
	URL = url;
}

const std::string& RequestLine::getVersion () const {
	return httpversion;
}

void RequestLine::setVersion (const std::string& v) {
	httpversion = v;
}

void RequestLine::clear (void) {
	method.clear ();
	URL.clear ();
	httpversion.clear ();
	isparsed = false;
}

bool RequestLine::isParsed () const {
	return isparsed;
}


std::vector<std::string>    RequestLine::split(std::string str, std::string delim)
{
    std::vector<std::string>    vec;
	size_t				check_double_space;

    // str = ltrim(str, delim);
    if (str[0] == delim[0] || str[str.size() - 1] == delim[0])
    {
        // std::cout << "syntaxe space error\n";
        // ERROR
    }
    std::string     limit;
    while (str.compare(""))
    {
		check_double_space = str.find_first_of(delim);

		if (str.find_first_of(delim, check_double_space + 1) - check_double_space == 1)
		{
			// std::cout << "double space dedected\n";
			return vec;
			// ERROR
		}
        limit = str.substr(0, str.find_first_of(delim));
        vec.push_back(limit);
        str = str.substr(limit.size(), str.size());
        str = ltrim(str, delim);
    }
    return (vec);
}

bool RequestLine::parse (const std::string& input) {

	std::vector<std::string>	line = split(input, " ");
	//to check the CRLF !!
	if (line.size() != 3)
	{
		return false;
		// ERROR !!!!!
	}
	method = line[0];
	URL = URI(line[1]);
	httpversion = line[2];
	isparsed = true;
	// parse the method : 405 (method not allowed) || 501 (Not implemented )
	return true;
}

void RequestLine::print () const {
	std::cout << method << " " << URL._host << " " << httpversion << "\n";
}
