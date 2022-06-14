#ifndef __ROOT_HPP__
#define __ROOT_HPP__

#include "SimpleCompoent.hpp"

class Root: public SimpleComponent {
	private:
		std::string			root;
	public:
		Root ();
		Root (const Root&);
		Root& operator =(const Root&);
		~Root ();
		Component* clone () const {
			return new Root (*this);
		};
		void print () const;
		bool isSet () const;
		void setRoot (const std::string& rt) { root = rt; };
		void parse (Tokenizer& );
		std::string	getRoot() const {	return root;	}
};

#endif