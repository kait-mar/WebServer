#include "Payload.hpp"

#include <unistd.h>
#include "../utility/file_utility.hpp"
#include <iostream>

Payload::Payload () {
	buffer = new std::string ();
}
Payload::~Payload () {
	delete buffer;
}

void Payload::setFile (int _fd) {
	*buffer = readfromFile (_fd);
}

void Payload::setBuffer (const std::string& str) {
	*buffer = str;
}

void Payload::setBuffer (std::string *buff) {
	delete buffer;
	buffer = buff;
}

size_t Payload::size () const {
	return buffer->size ();
}

std::string Payload::body () const {
	return *buffer;
}

void Payload::clear () {
	this->buffer->clear ();
}

void Payload::addBytes (const std::string& bytes) {
	*buffer += bytes;
}

void Payload::print () const {
	std::cout << "BODYSIZE : " << this->size () << " " << std::endl;
	std::cout << *(this->buffer) << std::endl;
}