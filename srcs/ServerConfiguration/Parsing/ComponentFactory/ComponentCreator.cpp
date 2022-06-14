#include "ComponentCreator.hpp"


// Component creator
// a singlton that can generate any configuration
// component

#include "../Components/AllowedMethods.hpp"
#include "../Components/AutoIndex.hpp"
#include "../Components/BodySize.hpp"
#include "../Components/BracketedComponent.hpp"
#include "../Components/CgiPass.hpp"
#include "../Components/ErrorPages.hpp"
#include "../Components/Index.hpp"
#include "../Components/Listen.hpp"
#include "../Components/Return.hpp"
#include "../Components/Root.hpp"
#include "../Components/ServerNames.hpp"
#include "../Components/SuffixBracketedComponent.hpp"
#include "../Components/Upload.hpp"

ComponentCreator::ComponentCreator () {};

ComponentCreator *ComponentCreator::creator = 0x0;

ComponentCreator* ComponentCreator::instance () {
	if (!creator) {
		creator = new ComponentCreator ();
		creator->mp = new std::map<std::string, std::pair<COMP, Component*> > ();
		creator->mp->insert (std::make_pair ("listen", std::make_pair(LISTEN, new Listen ())));
		creator->mp->insert (std::make_pair ("root", std::make_pair(ROOT, new Root ())));
		creator->mp->insert (std::make_pair ("index", std::make_pair(INDEX, new Index ())));
		creator->mp->insert (std::make_pair ("auto_index", std::make_pair(AUTOINDEX, new AutoIndex ())));
		creator->mp->insert (std::make_pair ("max_body_size", std::make_pair(BODYSIZE, new BodySize ())));
		creator->mp->insert (std::make_pair ("allowed_methods", std::make_pair (ALLOWEDMETHODS, new AllowedMethods ())));
		creator->mp->insert (std::make_pair ("error_page", std::make_pair(ERRORPAGES, new ErrorPages ())));
		creator->mp->insert (std::make_pair ("server_name", std::make_pair (SERVERNAMES, new ServerNames ())));
		creator->mp->insert (std::make_pair ("upload", std::make_pair (UPLOAD, new Upload ())));
		creator->mp->insert (std::make_pair ("cgi_pass", std::make_pair (CGIPASS, new CgiPass ())));
		creator->mp->insert (std::make_pair ("return", std::make_pair (RETURN, new Return ())));
		creator->mp->insert (std::make_pair ("location", std::make_pair (LOCATION, 
												new SuffixBracketedComponent ("location", false, ROOT | INDEX | AUTOINDEX | ERRORPAGES | ALLOWEDMETHODS | UPLOAD| RETURN | CGIPASS))));
		creator->mp->insert (std::make_pair ("server", std::make_pair (SERVER, 
												new BracketedComponent ("server", false, LISTEN | ROOT | INDEX | ERRORPAGES | SERVERNAMES | LOCATION | RETURN))));
		creator->mp->insert (std::make_pair ("http", std::make_pair (HTTPCONFIG, 
												new BracketedComponent ("http", true, ROOT | SERVER | BODYSIZE ))));
	}
	return creator;
}

COMP ComponentCreator::id (const std::string & _dir) {
	std::map<std::string,std::pair<COMP, Component *> >::const_iterator it = mp->find (_dir);
	if (it == mp->end ()) return UNKNOWN;
	return it->second.first;
}

Component	*ComponentCreator::create (const std::string& _dir) {
	std::map<std::string,std::pair<COMP, Component *> >::const_iterator it = this->mp->find (_dir);
	if (it == mp->end ()) return nullptr;
	return it->second.second->clone ();
}
