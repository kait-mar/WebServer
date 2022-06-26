//
// Created by Mouaad Labhairi on 6/3/22.
//

#ifndef WEB_SERVER_CGISTATE_HPP
#define WEB_SERVER_CGISTATE_HPP

#include "State.hpp"
#include "../SelectionAlgo/SelectionAlgo.hpp"

class CgiState : public State {
private:
	std::string _url;
	std::string _exec;
	Server	*_server;
	Location	*_location;
public:
	CgiState(std::string&, std::string&, Server*, Location*);
	void handle();

};


#endif //WEB_SERVER_CGISTATE_HPP
