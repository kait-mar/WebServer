#ifndef __REDIRECT_GENERATOR_HPP__
#define __REDIRECT_GENERATOR_HPP__

#include "ResponseGenerator.hpp"
#include "../utility/time_utility.hpp"

class RedirectGenerator: public ResponseGenerator {
    private:
        unsigned short code;
        std::string path;
    public:
        RedirectGenerator (unsigned short, const std::string&);
        ~RedirectGenerator ();
        void add_response_line ();
		void add_header_fields ();
};

#endif