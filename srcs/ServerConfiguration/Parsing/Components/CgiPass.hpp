//
// Created by Mouaad Labhairi on 6/1/22.
//

#ifndef WEB_SERVER_CGIPASS_HPP
#define WEB_SERVER_CGIPASS_HPP

#include "SimpleCompoent.hpp"

class CgiPass: public SimpleComponent {
private:
	std::map <std::string, std::string> cgis;
public:
	CgiPass ();
	CgiPass (const CgiPass&);
	CgiPass& operator = (const CgiPass& );
	~CgiPass ();
	Component* clone () const {
		return new CgiPass (*this);
	};
	bool isSet () const;
	void print () const;
	void parse (Tokenizer& );
	std::map <std::string, std::string>& get_map();
};

#endif //WEB_SERVER_CGIPASS_HPP
