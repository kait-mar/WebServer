#include "ConfigFileParser.hpp"
#include <iostream>

#include "../Components/Components.hpp"

ConfigFileParser::ConfigFileParser (const char *_path) {
	if (_path) path = _path;
}

Component* ConfigFileParser::parse () const {
	Component *UserHttpConfig = nullptr;
	
	if (!path.size ())
		return nullptr;
	std::ifstream is (path, std::ifstream::in);
	if (!(is.is_open ())) {
		std::cerr << "Can't open file " << path << std::endl;
		return UserHttpConfig;
	}
	Tokenizer tokenizer (is);
	UserHttpConfig = ComponentCreator::instance ()->create ("http");
	try {
		UserHttpConfig->syntax_parse (tokenizer);
		this->format (UserHttpConfig);
		//UserHttpConfig->pretty_print ();	
	}
	catch (std::exception& e) {
		std::cerr << e.what () << std::endl;
		delete UserHttpConfig;
		UserHttpConfig = nullptr;
	}
	return UserHttpConfig;
}

void ConfigFileParser::format (Component *HttpConfig) const {
	if (!HttpConfig) return;

	Root *root = HttpConfig->getSimpleAttribute_<Root> ();
	if (!root)
		throw std::runtime_error ("root is required in http block\n");
	BodySize *bodysize = HttpConfig->getSimpleAttribute_<BodySize> ();
	if (!bodysize)
		HttpConfig->addSubComponent (new BodySize (80));

	std::vector<Server *> vservers = HttpConfig->getSubComponents_<Server> ();
	if (vservers.empty ())
		throw std::runtime_error ("no server block in config file\n");
	for (std::vector<Server*>::iterator it = vservers.begin (); it != vservers.end (); ++it) {
		if ((!(*it)->getSimpleAttribute_ <Listen> ()))
			(*it)->addSubComponent (ComponentCreator::instance ()->create ("listen"));
		if ((!(*it)->getSimpleAttribute_<Root> ()))
			(*it)->addSubComponent (new Root (*root));

		std::vector<Location*> locations = (*it)->getSubComponents_<Location> ();
		if (locations.empty ())
			throw std::runtime_error ("Location is required in Server block\n");
		for (std::vector<Location*>::iterator iter = locations.begin (); iter != locations.end (); ++iter) {
			AllowedMethods *methods = (*iter)->getSimpleAttribute_<AllowedMethods> ();
			if (!methods)
				(*iter)->addSubComponent (new AllowedMethods (true));
		}
	}

}