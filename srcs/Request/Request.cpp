#include "Request.hpp"

Request::Request () {
	requestline = new RequestLine ();
	hf = new HeaderFields ();
	pl = new Payload ();
}

Request::~Request () {
	delete requestline;
	delete hf;
	delete pl;
}


bool Request::parse (const std::string& input) {
	if (!requestline->isParsed ())
		return requestline->parse (input);
	if (!hf->isParsed ())
		return hf->parse (input);
	return true;
}

bool Request::isParsed () const {
	return requestline->isParsed () && hf->isParsed ();
}

void Request::clear () {
	requestline->clear ();
	hf->clear ();
	pl->clear ();
}

void Request::print () const {
	requestline->print ();
	hf->print ();
	pl->print ();
}

RequestLine *Request::get_requestLine() {
	return requestline;
}

HeaderFields *Request::get_headerFields() {
	return hf;
}


const HeaderFields&	Request::getHeaderFields() const {
	return *hf;
}

HeaderFields& Request::getHeaderFields () {
	return *hf;
}

const RequestLine&	Request::getRequestLine() const {
	return *requestline;
}

RequestLine&	Request::getRequestLine() {
	return *requestline;
}

const Payload& Request::getRequestBody () const {
	return *pl;
}

Payload& Request::getRequestBody() {
	return *pl;
}

