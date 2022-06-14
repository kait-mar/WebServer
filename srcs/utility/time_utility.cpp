#include "time_utility.hpp"

#include <time.h>

std::string httpDateTime () {
	char buffer[256];

	time_t timestamp = time (NULL);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", localtime (&timestamp));

	return buffer;
}