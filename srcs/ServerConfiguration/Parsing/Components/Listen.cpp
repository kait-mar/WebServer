#include "Listen.hpp"

#include <arpa/inet.h>

// must respect network byte order
Address::Address (): is_set (false), address (0) {}
Address::Address (const Address& _rhs): is_set (_rhs.is_set), address (_rhs.is_set) {}
Address& Address::operator= (const Address& _rhs) {
	if (this != &_rhs) {
		is_set = _rhs.is_set;
		address = _rhs.address;
	}
	return *this;
}

Address::Address (const std::string& ad) {
	struct in_addr addr;
	if (inet_pton (AF_INET, ad.c_str (), &addr.s_addr) == 1) {
		is_set = true;
		address = addr.s_addr;
	}
	else
		address = 0;
}

Address::~Address () {}
u_int32_t Address::getAdress () const { return address; }
void Address::setAddress (u_int32_t addr) { address = addr; }
const char *Address::print () const {
	struct in_addr addr;
	addr.s_addr = address;
	return inet_ntoa (addr);
}
void Address::parse (Tokenizer& tokenizer) {
	std::string address_token = tokenizer.id ();
	
	if (address_token.find ('.') != std::string::npos){
		struct in_addr addr;
		if (inet_pton (AF_INET, address_token.c_str (), &addr.s_addr) == 1) {
			is_set = true;
			address = addr.s_addr;
			++tokenizer;
			return;
		}
		throw Error (tokenizer.error("expected address"));
	}
}
bool	Address::operator==(const Address& adr)	{	return (address == adr.address);	}
bool	Address::operator!=(const Address&adr)	{	return !operator==(adr);			}

Port::Port ():  is_set (false), port (80) {}
Port::Port (const std::string& prt) {
	port = ::atoi (prt.c_str ());
	is_set = true;
}

Port::Port (const Port& _rhs): is_set (_rhs.is_set), port (_rhs.is_set) {}
Port& Port::operator= (const Port& _rhs) {
	if (this != &_rhs) {
		is_set = _rhs.is_set;
		port = _rhs.port;
	}
	return *this;
}

Port::~Port () {}
u_int16_t Port::getPort () const { return port; }
void Port::setPort (u_int16_t prt) { port = prt; }
void Port::parse (Tokenizer& tokenizer) {
	std::string address = tokenizer.id ();
	if (!(*tokenizer).is_directive ()) {
		if (all_of_ (address.begin (), address.end (), is_digit ())) {
			unsigned int prt = std::atoi (address.c_str ());
			if (prt <= 0xFFFF) {
				++tokenizer;
				port = prt;
				is_set  = true;
			}
		}
		else
			throw Error (tokenizer.error ("wrong port"));
	}
}
bool	Port::operator==(const Port& por)	{	return (port == por.port);	}
bool	Port::operator!=(const Port& por)	{	return (port != por.port);	}

Listen::Listen (): SimpleComponent ("listen") {}
Listen::Listen (const Listen& _rhs): SimpleComponent (_rhs), _addr (_rhs._addr), _prt (_rhs._prt) {}

Listen& Listen::operator= (const Listen& _rhs) {
	if (this != &_rhs) {
		_addr = _rhs._addr;
		_prt = _rhs._prt;
	}
	return *this;
}


Listen::~Listen () {}
bool Listen::isSet () const { return _prt.isSet () || _addr.isSet (); }
void Listen::parse (Tokenizer& tokenizer) {
	_addr.parse (tokenizer);
	_prt.parse (tokenizer);
}

void Listen::print () const {
	std::cout << _addr.print() << ":" << _prt.getPort ();
}