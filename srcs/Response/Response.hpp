#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include <string>
#include <map>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../Response/Payload.hpp"
#include "../ServerConfiguration/Configuration.hpp"
#include "../utility/CaseInsensitiveLess.hpp"

class Response {
	private:
		std::string		http_version;
		std::string		status_code;
		std::string		reason_phrase;
		std::map <std::string, std::string, CaseInsensitveLess> headerfields;
		Payload			pl;
		std::vector<std::string> coockies;
	public:
		Response ();
		void clear ();
		void setVersion (const std::string&);
		void setStatusCode (const std::string&);
		void setReasonPhrase (const std::string&);
		void addHeaderField (const std::string&, const std::string&);
		std::string getStatusLine () const;

		std::string getHeadersSection () const;
		std::map<std::string, std::string, CaseInsensitveLess>& getHeaderfields ();
		Payload& getPayload () {
			return pl;
		}
		std::string	getReasonPhrase() const;
		int			is_directory(const std::string&);
		
		void addCoockie (const std::string&);
		const std::vector<std::string>& getCoockies () const;
};

class Host
{
public:
	std::string	_host;
	Port		_prt;
	Address		addr;
	int			is_addr;
	int			is_prt;
	int			is_server_name;

	Host(std::string host):_host(host), is_addr(0), is_prt(1), is_server_name(0) {}
	void	check();
	~Host() {}
};



#endif