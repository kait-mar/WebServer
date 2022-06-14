#include "utility.hpp"

std::string g_trim(std::string str, std::string delim)
{
    size_t begin = str.find_first_not_of(delim);
    size_t  end = str.find_first_of(delim, begin);
    return (str.substr(begin, end));
}

// std::string     ltrim(std::string str, std::string delim)
// {
//     size_t begin = str.find_first_not_of(delim);
//     if (begin == std::string::npos)
//         return ("");
//     return (str.substr(begin));
// }

std::string     ltrim(std::string str, std::string delim)
{
    size_t i;
    for (i = 0; i < delim.size(); i++)
    {
        if (i >= str.size() || str[i] != delim[i])
            break;
    }
    if (i == delim.size() && i <= str.size())
        str = str.substr(i); 
    return (str);
}

std::vector<std::string>    split(std::string str, std::string delim)
{
    std::vector<std::string>    vec;
    int                         check_double_space;

    // str = ltrim(str, delim);
    if (str == "")
        return (std::vector<std::string>());
    if (str[0] == delim[0])
    {
        // std::cout << "syntaxe space error\n";
        // ERROR
    }
    std::string     limit;
    while (str.compare(""))
    {
        check_double_space = str.find_first_of(delim);
		// if (check_double_space - str.find_first_of(delim, check_double_space + 1) == -1)
		// {
		// 	std::cout << "double space dedected\n";
		// 	// return vec;
		// 	// ERROR
		// }
        limit = str.substr(0, str.find_first_of(delim));
        vec.push_back(limit);
        str = str.substr(limit.size(), str.size());
        str = ltrim(str, delim);
    }
    return (vec);
}

int             find_repit(std::string str, char c)
{
    int num = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == c)
            num++;
    }
    return (num);
}

// int main()
// {
//     std::string str = "/tmp/Response";
//     str = ltrim(str, "/tmp");
//     int i = 0;
//     std::cout << str << std::endl;
//     // while (i < vec.size())
//     //     std::cout << vec[i++] << std::endl;
// }