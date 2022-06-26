#ifndef __TRANSFER_ENCODING_HPP__
#define __TRANSFER_ENCODING_HPP__

#include "Filter.hpp"

class TransferEncodingFilter: public Filter {
	public:
		TransferEncodingFilter (): Filter (505) {}
		bool apply (const Request& request) const {
			std::cout << request.getHeaderFields ()["Transfer-Encoding"]  << std::endl;
			if (request.getHeaderFields ().has ("Transfer-Encoding")) {
				if (request.getHeaderFields ()["Transfer-Encoding"] != "chunked")
					return false;
			}
			return true;
		}
};
#endif