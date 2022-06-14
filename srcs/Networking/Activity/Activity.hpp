#ifndef __ACTIVITY_HPP__
#define __ACTIVITY_HPP__

#include <sys/time.h>


/*********************************************
 *	record the last time an event of READ or
 * 	WRITE has been set on the dataConnection
 *  the object is attached to.
 *********************************************/
class Activity {
	private:
		struct timeval time; 
	public:
		Activity ();
		~Activity ();
		bool timeOut () const;
		void reset ();
};


#endif