#ifndef __MULTIPLEXER_HPP__
#define __MULTIPLEXER_HPP__

#include <map>
#include "../Connections/Connection.hpp"
#include <vector>

class	Multiplexer {
	protected:
		std::map <int, Connection *> screen;
		std::vector <Connection *> pendings;
		std::map<int, Connection *>::iterator iter;
	public:
		Multiplexer ();
		Multiplexer (const Multiplexer&);
		virtual ~Multiplexer () {}
		virtual bool change () const = 0;
		void Register (Connection *);
		void First ();
		void Next ();
		Connection *Current () const;
		bool isDone () const;
		void Unregister (Connection *);
		virtual bool Monitor () = 0;
};

#endif