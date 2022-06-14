#include "Uri.hpp"

#include <string>
#include <vector>
#include "../utility/utility.hpp"

URI::URI(std::string str): _host(str) {}
URI::URI(): _host("") {}

std::string	URI::ressource()
{
	// _host = ltrim(_host, "http://");
	// _host = ltrim(_host, hf.getHf()["host"]); i think no need !!
	std::vector<std::string>	param = split(_host, "?");
	if (param.size())
		_ressource = param[0];
	if (param.size() > 1)
		_query = param[1];
	return _ressource;
}

void	URI::clear()
{
	_uri.clear();
	_host.clear();
	_ressource.clear();
	_query.clear();
}

std::string	URI::file(std::string str)
{
	ressource();
	_ressource = ltrim(_ressource, str);
	return _ressource;
}