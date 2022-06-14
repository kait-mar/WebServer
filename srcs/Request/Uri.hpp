#ifndef __URI_HPP__
#define __URI_HPP__

#include <string>

class URI {
	public:
		std::string	_uri;
		std::string	_host;
		std::string	_ressource;
		std::string	_query;

		URI(std::string);
		URI();
		~URI() {}
		std::string	ressource();
		std::string	file(std::string);
		void	query();
		void	clear();
};

#endif