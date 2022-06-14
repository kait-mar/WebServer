#ifndef __INDEX_HPP__
#define __INDEX_HPP__

#include "SimpleCompoent.hpp"

class Index: public SimpleComponent {
	private:
		std::vector <std::string>	indexes;
	public:
		Index ();
		Index (const Index&);
		Index& operator = (const Index& );
		~Index ();
		void print () const;
		Component* clone () const {
			return new Index (*this);
		};
		bool isSet () const;
		void addIndex (const std::string& idx);
		void parse (Tokenizer& );
		std::vector <std::string>	&getIndexes() { return indexes;}
};

#endif