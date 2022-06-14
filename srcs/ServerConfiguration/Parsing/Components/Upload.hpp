#ifndef __UPLOAD_HPP__
#define __UPLOAD_HPP__

#include "SimpleCompoent.hpp"

class Upload: public SimpleComponent {
	private:
		std::string			root;
	public:
		Upload ();
		Upload (const Upload&);
		Upload& operator =(const Upload&);
		~Upload ();
		Component* clone () const {
			return new Upload (*this);
		};
		
		void print () const;
		bool isSet () const;
		void setRoot (const std::string& rt);
		void parse (Tokenizer& );
		std::string	&getRoot()	{	return root; }
};

#endif