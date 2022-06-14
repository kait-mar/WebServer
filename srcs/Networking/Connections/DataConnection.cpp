#include "DataConnection.hpp"

#include <unistd.h>

#include "../../ServerConfiguration/Configuration.hpp"

#include "../../State/StartState.hpp"
#include "../../State/CloseState.hpp"


dataConnection::dataConnection (int fd): Connection (fd) {
    Configuration::instance ()->getLogger ().AccessLog ("New", *this);
    outputBuffer 	= new OutputBuffer (fd);
	inputBuffer 	= new InputBuffer ();
	activity    	= new Activity ();
    request     	= new Request ();
    response    	= new Response ();
	state			= nullptr;
	close			= false;
	this->TranslationTo (new StartState ());
}

dataConnection::~dataConnection () {
	delete activity;
	delete request;
	delete response;
	delete outputBuffer;
	delete state;
}

Request *dataConnection::getRequest () {
	return request;
}
  
bool dataConnection::isClose () const {
	return close;
}

void dataConnection::SetState (State *_state) {
	this->state = _state;
}


InputBuffer& dataConnection::getInputBuffer () {
	return *inputBuffer;
}

OutputBuffer& dataConnection::getOutputBuffer () {
	return *outputBuffer;
}

bool dataConnection::getClose () {
	return close;
}

void dataConnection::setClose () {
	close = true;
}

void dataConnection::TranslationTo (State *_state) {
	if (this->state != nullptr)
		delete state;
	this->state = _state;
	this->state->setContext (this);
	this->activity->reset ();
}

void dataConnection::handle () {
	if (this->activity->timeOut ()) {
		this->TranslationTo (new CloseState ());
		return;
	}
	state->handle ();
}

Response 	*dataConnection::getResponse () {
	return response;
}

void dataConnection::setResponse (Response *_response) {
	if (response)
		delete response;
	response = _response;
}

Activity& dataConnection::getActivity () {
	return *activity;
}

