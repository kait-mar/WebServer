#ifndef __PAYLOAD_HPP__
#define __PAYLOAD_HPP__

#include <stddef.h>
#include <string>

class Payload {
private:
	std::string *buffer;
public:
	Payload ();
	~Payload ();
	size_t size () const;
	void setFile (int);
	void addBytes (const std::string&);
	void setBuffer(const std::string&);
	void setBuffer (std::string*);
	void print () const;
	std::string body () const;
	void clear ();
};


#endif