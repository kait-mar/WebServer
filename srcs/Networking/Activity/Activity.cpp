#include "Activity.hpp"

#include "../../ServerConfiguration/Configuration.hpp"

Activity::Activity () {
	this->reset ();	
}

Activity::~Activity () {}

bool Activity::timeOut () const {
	struct timeval now;
	gettimeofday (& now, 0x0);
	now.tv_sec -= Configuration::instance ()->keepAlive ();
	if (time.tv_sec < now.tv_sec) return true;
	if (time.tv_sec == now.tv_sec && time.tv_usec <= now.tv_usec) return true;
	return false;
}

void Activity::reset () { gettimeofday (&time, 0x0); }
