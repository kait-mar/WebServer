#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include "../Logger/Logger.hpp"
#include "Parsing/Components/Components.hpp"
#include "Parsing/ComponentFactory/ComponentCreator.hpp"
#include "Parsing/Parser/ConfigFileParser.hpp"


class Configuration {
	private:
		static Configuration		*conf;
		Component 					*UserHttpConfig;
		static const unsigned int	keepalive = 180;
		Logger						logger;
		Configuration ();
	public:
		static	Configuration* instance ();
		void setUSerConfig (Component *);
		Logger& getLogger ();
		unsigned int keepAlive() const;
		Component *getConfigurations () const;
		static std::string serverName ();
		static std::string codeToReasonPhrase (unsigned short code);
		static std::string mimeType (const std::string& extension);
};


#endif