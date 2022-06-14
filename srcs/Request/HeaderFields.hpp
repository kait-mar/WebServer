#ifndef __HEADER_FIELDS_HPP__
#define __HEADER_FIELDS_HPP__

#include <map>
#include <string>
#include <vector>
#include "../utility/utility.hpp"

#include "../utility/CaseInsensitiveLess.hpp"

class HeaderFields {
	public:
		typedef std::map <std::string, std::string, CaseInsensitveLess> headers;
	private:
		headers hf;
		bool isparsed;
	public:
		HeaderFields ();
		~HeaderFields ();
		bool parse (const std::string&);
		void print () const;
		bool isParsed () const;
		void	clear();
		headers get_hf();
		headers getHf() {	return hf;	}
		const std::string	&operator[](const std::string &str) {	return hf[str];	}
		size_t size () const;
		bool has (const std::string&) const;
		const std::string& getHeader (const std::string&);
		void add (const std::string&, const std::string&);
		void remove(const std::string&);
		const std::string& operator [] (const std::string&) const;
};


#endif