#ifndef __BODY_SIZE_HPP__
#define __BODY_SIZE_HPP__

#include "SimpleCompoent.hpp"

class BodySize: public SimpleComponent {
	private:
		unsigned int size;
		bool already_set; 
	public:
		BodySize ();
		BodySize (unsigned int );
		BodySize (const BodySize&);
		BodySize& operator = (const BodySize& );
		~BodySize ();
		Component * clone () const {
			return new BodySize (*this);
		}
		void print () const;
		bool isSet () const;
		void setBodySize (unsigned int);
		unsigned int getBodySize () const;
		void parse (Tokenizer& );
};

#endif