#include "Event.hpp"

Event::Event (): event (0) {}
Event::Event (int e): event (e & (READ | WRITE)) {}
Event::~Event () {}
Event::operator bool () const {
	return event;
}
Event::operator short () const {
	return event;
}

void Event::set (E e) {
	event |= e;
}

bool Event::operator == (int e) const { return (event & e); }
