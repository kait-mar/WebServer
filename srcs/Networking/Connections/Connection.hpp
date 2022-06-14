#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <string>

/********************************************
 *	Connection base class: handle the type of 
 *	the connection and the file descriptor
 * 	associated with it.
 *******************************************/

#include "../../Event/Event.hpp"

class Connection {
	private:
		Event			event;
		int				fd;
	public:
		Connection (int);
		virtual  ~Connection ();
		virtual	bool getClose () = 0;
		virtual void handle () = 0;
		void	setEvent (Event e);
		const Event&	getEvent () const;
		int		getFd () const;
		void	close ();
};

#endif