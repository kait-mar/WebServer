#ifndef __FILTERS_UTILITY_HPP__
#define __FILTERS_UTILITY_HPP__

#include <string.h>

static const char allowedCharInUrl [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
								 "jklmnopqrstuvwxyz0123456789-._~:/?#"
								 "[]@!$&'()*+,;=%";
struct is_in {
	bool operator () (char c) {
		return ::strchr (allowedCharInUrl, c) != NULL;
	}
};

namespace cpp98 {
	template<class InputIterator, class UnaryPredicate>
	bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		while (first!=last) {
			if (!pred(*first)) return false;
			++first;
		}
		return true;
	}
}

#endif