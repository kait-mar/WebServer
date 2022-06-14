#ifndef __MAL_FORMED_URL_HPP__
#define __MAL_FORMED_URL_HPP__

#include "Filter.hpp"
#include "../../utility/FiltersUtility.hpp"


class MalFormedUrl: public Filter {
	public:
		MalFormedUrl (): Filter (400) {}
		bool apply (const Request& request) const {
			return cpp98::all_of (request.getRequestLine ().getURL()._host.cbegin (),
				request.getRequestLine ().getURL ()._host.cend (), is_in ());
		}
};

#endif