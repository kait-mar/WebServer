#include "file_utility.hpp"
#include "unistd.h"

size_t file_size (int fd) {
	struct stat stt;

	fstat (fd, &stt);
	return stt.st_size;
};

std::string readfromFile (int fd) {
	std::string buffer;
	char buff[1024];

	ssize_t ret;
	while (1) {
		ret = ::read (fd, buff, 1024);
		if (ret <= 0) break;
		buffer.append (buff, buff + ret);
	}
	return buffer;
}

int		is_directory(const std::string &str)
{
	const char	*path = str.c_str();
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
