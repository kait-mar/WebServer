#ifndef __FILE_UTILITY_HPP__
#define __FILE_UTILITY_HPP__

#include <sys/stat.h>
#include <stddef.h>
#include <string>
#include <iostream>
#include <fstream>

size_t file_size (int fd);

std::string readfromFile (int fd);
int			is_directory(const std::string&);

#endif