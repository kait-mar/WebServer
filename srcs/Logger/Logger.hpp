#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>
class Connection;

/************************************************
 * logger:
 * 		AccessLog: log new dataConnections
 * 		ErrorLog:	log errors
 * *********************************************/
class Logger {
	private:
		int 	errorfd;
		int		accessfd;
	public:
		Logger (const std::string& error= "./tmp/error.log", 
				const std::string& access = "./tmp/access.log");
		~Logger ();
		void ErrorLog (const std::string&) const;
		void AccessLog (const std::string&) const;
		void AccessLog (const std::string& log, const Connection& con) const;
};

#endif