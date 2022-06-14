#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include <poll.h>

enum  E {
	READ = POLLIN,
	WRITE = POLLOUT
};

class Event {
	private:
		int event;
	public:
		Event	();
		Event	(int e);
		~Event	();
		void set (E);
		operator bool () const;
		operator short () const;
		bool operator == (int e) const;
};

#endif

