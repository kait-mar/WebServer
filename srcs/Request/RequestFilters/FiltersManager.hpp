#ifndef __FILTERS_MANAGER_HPP__
#define __FILTERS_MANAGER_HPP__

#include "Filter.hpp"
#include "../Request.hpp"

class FiltersManager {
	private:
		typedef std::vector<Filter *> filters;
		filters pipeline;
	public:
		FiltersManager ();
		~FiltersManager ();
		void addFilter (Filter *);
		unsigned short filter (const Request&) const;
};

#endif