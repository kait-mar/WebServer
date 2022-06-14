#ifndef __INPUT_BUFFER_HPP__
#define __INPUT_BUFFER_HPP__

#include <string>

class InputBuffer {
	private:
		std::string	buffer;
	public:
		InputBuffer ();
		~InputBuffer ();
		bool read (int fd);
		void print ();
		std::string* getPart(size_t);
		bool getNextLine (std::string&);
		size_t size () const;

};

#endif