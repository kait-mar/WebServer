#ifndef __LISTEN_HPP__
#define __LISTEN_HPP__

#include "SimpleCompoent.hpp"

class Address {
	private:
		bool is_set;
		u_int32_t address;
	public:
		Address ();
		~Address ();
		Address (const std::string&);
		Address (const Address& _rhs);
		Address& operator = (const Address&);
		bool isSet () const { return is_set; }
		const char* print () const;
		u_int32_t getAdress () const;
		void setAddress (u_int32_t addr);
		void parse (Tokenizer& );
		bool	operator==(const Address&);
		bool	operator!=(const Address&);
};

class Port {
	private:
		bool is_set;
		u_int16_t port;
	public:
		Port ();
		Port (const std::string&);
		Port (const Port&);
		Port& operator = (const Port&);
		~Port ();
		bool isSet () const { return is_set; }
		u_int16_t getPort () const;
		void setPort (u_int16_t prt);
		void parse (Tokenizer& );
		bool	operator==(const Port&);
		bool	operator!=(const Port&);
};

class Listen: public SimpleComponent {
	private:
		Address _addr;
		std::string address_str;
		std::string port_str;
		Port	_prt;
	public:
		Listen ();
		Listen (const Listen&);
		Listen& operator = (const Listen&);
		~Listen ();
		Component* clone () const {
			return new Listen (*this);
		};
		void print () const;
		bool isSet () const;
		void parse (Tokenizer& );
		u_int32_t getAddress () const { return _addr.getAdress (); }
		u_int16_t getPort () const { return _prt.getPort (); }
		Address getAddress_ () const { return _addr; }
		Port getPort_ () const { return _prt; }
};


#endif