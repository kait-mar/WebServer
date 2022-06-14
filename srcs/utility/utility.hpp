#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <vector>
#include <string>
#include <iostream>


std::vector<std::string>    split(std::string, std::string);
std::string                 g_trim(std::string, std::string);
std::string     ltrim(std::string, std::string);
int             find_repit(std::string, char c);
#endif