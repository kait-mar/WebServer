#ifndef __RETURN_HPP__
#define __RETURN_HPP__

#include "SimpleCompoent.hpp"

class Return: public SimpleComponent {
	private:
		unsigned short code;
		std::string _code;
		std::string path;
		bool is_set;
	public:
		Return ();
		Return (const Return&);
		Return& operator = (const Return& );
		~Return ();
		Component* clone () const {
			return new Return (*this);
		};
		void print () const;
		bool isSet () const;
		void parse (Tokenizer& );
		unsigned short getCode () const;
		std::string getPath () const;
};

#endif