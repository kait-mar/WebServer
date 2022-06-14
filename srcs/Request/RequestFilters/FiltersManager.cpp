#include "FiltersManager.hpp"

FiltersManager::FiltersManager () {}
FiltersManager::~FiltersManager () {
	for (filters::iterator it = pipeline.begin (); it != pipeline.end (); ++it)
		delete *it;
}

void FiltersManager::addFilter (Filter *filter) {
	pipeline.push_back (filter);
}

unsigned short FiltersManager::filter (const Request& request) const {
	for (filters::const_iterator it = pipeline.cbegin (); it != pipeline.cend (); ++it) {
		unsigned short code = (*it)->filter (request);
		if (code) return code;
	}
	return 0;
}
