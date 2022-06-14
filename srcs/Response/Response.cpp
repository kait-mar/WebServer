#include "Response.hpp"

#include "../utility/utility.hpp"

std::string Response::getStatusLine () const {
	return http_version + " " + status_code + " " + reason_phrase + "\r\n";
}

std::string Response::getHeadersSection () const {
	std::string headersection;
	for (std::map<std::string, std::string>::const_iterator it = headerfields.begin (); it != headerfields.cend (); ++it) {
		headersection += (*it).first + ": " + (*it).second + "\r\n";
	}
	if (coockies.size ()) {
		for (std::vector<std::string>::const_iterator iter = coockies.cbegin (); iter != coockies.cend (); ++iter) {
			headersection += std::string ("Set-Cookie: ") + (*iter) + "\r\n";
		}
	}
	headersection += "\r\n";
	return headersection;
}


Response::Response (): http_version("HTTP/1.1") {}

void Response::clear () {
	http_version.clear ();
	status_code.clear ();
	reason_phrase.clear ();
	headerfields.clear ();
	pl.clear ();
	coockies.clear ();
}

void Response::setVersion (const std::string& version) {
	http_version = version;
}

void Response::setStatusCode (const std::string& status) {
	status_code = status;
}

void Response::setReasonPhrase (const std::string& reason) {
	reason_phrase = reason;
}

void Response::addHeaderField (const std::string& name, const std::string& value) {
	headerfields[name] = value;
}

std::map<std::string, std::string, CaseInsensitveLess>& Response::getHeaderfields () {
	return headerfields;
}

void Response::addCoockie (const std::string& coockie) {
	coockies.push_back (coockie);
}

const std::vector<std::string>& Response::getCoockies () const {
	return coockies;
}


void	Host::check()
{
	int	point = find_repit(_host, '.');
	std::vector<std::string>	vec;
	if (_host.find(":") != std::string::npos)
	{
		// is_prt = 1;
		vec = split(_host, ":");
		_host = vec[0];
		_prt = Port(vec[1]);
	}
	else
		_prt = Port("8080");
	if (point == 3)
	{
		is_addr = 1;
		addr = Address(_host);
	}
	else
	{
		is_server_name = 1;
	}
};
