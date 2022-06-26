#ifndef __BODY_SIZE_TOO_LARGE_HPP__
#define __BODY_SIZE_TOO_LARGE_HPP__

#include "Filter.hpp"
#include "../../ServerConfiguration/Configuration.hpp"

class BodySizeTooLarge: public Filter {
	public:
		BodySizeTooLarge (): Filter (413) {}
		bool apply (const Request& request) const {
			if (request.getHeaderFields ().has ("Content-Length")) {
				BodySize *maxBodySize = Configuration::instance ()->getConfigurations ()->getSimpleAttribute_<BodySize>();
				if (static_cast <unsigned int> (atoi (request.getHeaderFields()["Content-Length"].c_str())) > maxBodySize->getBodySize ())
					return false;
			}
			return true;
		}
};

#endif