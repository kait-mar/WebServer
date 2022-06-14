#ifndef __COMPONENT_CREATOR_HPP__
#define __COMPONENT_CREATOR_HPP__


#include <map>

#include "../Components/Component.hpp"

enum COMP {
	UNKNOWN			=		0,
	LISTEN 			=		1 << 0,
	ROOT			=		1 << 1,
	INDEX			=		1 << 2,
	AUTOINDEX		= 		1 << 3,
	BODYSIZE		=		1 << 4,
	ALLOWEDMETHODS	=		1 << 5,
	ERRORPAGES 		=		1 << 6,
	SERVERNAMES		=		1 << 7,
	LOCATION		=		1 << 8,
	SERVER			=		1 << 9,
	HTTPCONFIG		=		1 << 10,
	UPLOAD			=		1 << 11,
	CGIPASS			= 		1 << 12,
	RETURN 			=		1 << 13
};

class ComponentCreator {
	private:
		static ComponentCreator *creator;
		ComponentCreator ();
		std::map <std::string, std::pair<COMP, Component *> > *mp;
	public:
		COMP					id (const std::string & _dir);
		Component				*create (COMP c);
		Component				*create (const std::string& _dir);
		static ComponentCreator *instance ();
};

#endif