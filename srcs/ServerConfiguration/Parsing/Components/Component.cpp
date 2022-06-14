#include "Component.hpp"

#include "../ComponentFactory/ComponentCreator.hpp"

Component::Component (const std::string& dir, bool sin, unsigned _sub):  _sin (sin), _dir (dir), _subs (_sub) {}
Component::Component (const Component& _rhs): _sin (_rhs._sin), _dir (_rhs._dir), _subs (_rhs._subs), _subComp (_rhs._subComp) {}
Component& Component::operator = (const Component& _rhs) {
	if (this != &_rhs) {
		_sin = _rhs._sin;
		_dir = _rhs._dir;
		_subComp = _rhs._subComp;
	}
	return *this;
}
Component::~Component () {
	for (std::multimap <std::string, Component *>::iterator it = _subComp.begin (); it != _subComp.end (); ++it)
		delete ((*it).second);
}

bool Component::isSet () const {
	return !_subComp.empty ();
}

bool Component::isSub (const std::string& dir) const {
	return (_subs & ComponentCreator::instance ()->id (dir));
}

void Component::addSubComponent (Component *sub) {
	if (isSub (sub->dir ())) {
		std::multimap <std::string, Component *>::iterator it = _subComp.find (sub->dir ());
		if (it != _subComp.end ()) {
			if (((*it).second)->sin ())
				return;
		}
		_subComp.insert (std::make_pair (sub->dir (), sub));
	}
}
