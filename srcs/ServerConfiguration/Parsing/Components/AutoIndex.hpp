#ifndef __AUTO_INDEX_HPP__
#define __AUTO_INDEX_HPP__

#include "SimpleCompoent.hpp"

class AutoIndex: public SimpleComponent {
	private:
		std::string on;
	public:
		AutoIndex ();
		AutoIndex (const AutoIndex&);
		AutoIndex& operator = (const AutoIndex& );
		~AutoIndex ();
		void print () const;
		AutoIndex* clone ();
		bool isSet () const;
		Component *clone () const {
			return new AutoIndex (*this);
		}
		void setAutoIndex (bool on);
		std::string &getAutoIndex ();
		void parse (Tokenizer& );
};

#endif