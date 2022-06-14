//
// Created by Mouaad Labhairi on 6/1/22.
//

#include "CgiPass.hpp"

#include "utils.hpp"

CgiPass::CgiPass (): SimpleComponent ("cgi_pass", false) {}
CgiPass::CgiPass (const CgiPass& _rhs): SimpleComponent (_rhs), cgis (_rhs.cgis) {}
CgiPass& CgiPass::operator = (const CgiPass& _rhs) {
	if (this != &_rhs)
		cgis = _rhs.cgis;
	return *this;
}
CgiPass::~CgiPass () {}

bool CgiPass::isSet () const { return !cgis.empty (); }
void CgiPass::parse (Tokenizer& tokenizer) {
	while (!(*tokenizer).is_directive ()) {
		std::string			extension;
		std::string			path;
		std::string token = (*tokenizer).id ();
		if (token.find (":") == std::string::npos)
			throw Error (tokenizer.error ("expecting .EXT:/PATH/TO/yy"));
		extension = token.substr (0, token.find (':'));
		path = token.substr (token.find (':') + 1);
		if (extension[0] == '.') {
            if (!path.empty ()) {
                if (cgis.insert (std::make_pair (extension, path)).second == false)
                   throw Error (tokenizer.error ("extension already set")); 
            }
            else
               throw Error (tokenizer.error ("empty path")); 
        }
        else
            throw Error (tokenizer.error ("expected an extension"));
		++tokenizer;
	}
}
void CgiPass::print () const {
	for (std::map <std::string, std::string>::const_iterator it = cgis.cbegin (); it != cgis.end (); ++it) {
		std::cout << it->first << ":" << it->second << " ";
	}
}

std::map<std::string, std::string>& CgiPass::get_map()
{
	return this->cgis;
}