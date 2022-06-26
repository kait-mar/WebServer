#include "Logger.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../Networking/Connections/Connection.hpp"
#include "../utility/time_utility.hpp"

Logger::Logger (const std::string& error, const std::string& access) {
	errorfd		= open (error.c_str (), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	accessfd	=  open (access.c_str (), O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

Logger::~Logger () {
	::close (errorfd);
	::close (accessfd);
}

void Logger::ErrorLog (const std::string& err) const {
	if (errorfd >= 0) {
		std::string tmp (httpDateTime ());
		tmp += " " + err;
		if (::write (errorfd, tmp.data (), tmp.size ()) <= 0)
			return;
	}
}

void Logger::AccessLog (const std::string& err) const{
	if (accessfd >= 0)
	{
		if (::write (accessfd, err.data (), err.size ()) <= 0)
			return;
	}
}

void Logger::AccessLog (const std::string& log, const Connection& con) const {
	if (accessfd >= 0) {
		struct		sockaddr_in address;
		socklen_t	address_len = sizeof (address);
		getpeername(con.getFd (), (struct sockaddr *)&address, &address_len);
		
		std::string tmp (httpDateTime ());
		tmp += " " + log;
		tmp += " Connection: ";
		tmp += inet_ntoa(address.sin_addr);
		tmp += ":";
		tmp += std::to_string (ntohs (address.sin_port));
		tmp += "\n";
		AccessLog (tmp);
	}
}
