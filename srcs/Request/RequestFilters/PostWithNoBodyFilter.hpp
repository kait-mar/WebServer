#ifndef __POST_WITH_NO_BODY_HPP__
#define __POST_WITH_NO_BODY_HPP__

#include "Filter.hpp"

class PostWithNoBody: public Filter {
	public:
		PostWithNoBody (): Filter (400) {}
		bool apply (const Request& request) const {
			return !((!request.getHeaderFields ().has ("Transfer-Encoding") &&
				!request.getHeaderFields ().has ("Content-Length") &&
				request.getRequestLine ().getMethod () == "POST"));
		}
};
#endif