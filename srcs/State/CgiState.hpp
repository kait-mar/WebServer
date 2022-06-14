//
// Created by Mouaad Labhairi on 6/3/22.
//

#ifndef WEB_SERVER_CGISTATE_HPP
#define WEB_SERVER_CGISTATE_HPP

#include "State.hpp"

class CgiState : public State {
private:
	std::string _url;
	std::string _exec;
public:
	CgiState(std::string&, std::string&);
	void handle();

};


#endif //WEB_SERVER_CGISTATE_HPP
