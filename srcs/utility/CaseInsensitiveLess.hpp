#ifndef __CASE_INSENSITIVE_LESS_HPP__
#define __CASE_INSENSITIVE_LESS_HPP__

#include <string>

struct CaseInsensitveLess {
	struct NoCaseCompare {
		bool operator () (const unsigned char& c1, const unsigned char& c2) const {
			return tolower (c1) < tolower (c2);
		}
	};
	bool operator () (const std::string& s1, const std::string& s2) const {
		return std::lexicographical_compare (s1.begin (), s1.end (), s2.begin (), s2.end (), NoCaseCompare ());
	}
};

#endif