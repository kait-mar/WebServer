#ifndef __RESPONSEFILLER_HPP__
#define __RESPONSEFILLER_HPP__

#include "Response.hpp"
#include "../utility/file_utility.hpp"
#include <dirent.h> 
#include <stdio.h>
#include "../State/ErrorState.hpp"
#include "../ServerConfiguration/Configuration.hpp"


#define IN_SERVER 1
#define IN_LOCATION 2

class ResponseFiller
{
private:
    dataConnection  *context;
    Server          *server;
    Location        *location;
    Response        *response;
    int             error;
    int             __is_cgi;
    std::string     cgi;
    std::string     _cgi_exec;
public:
    ResponseFiller();
    ResponseFiller(dataConnection*, Server*, Location*, Response*);
    void fill();
    int		execute_get(RequestLine&);
    int		execute_post(RequestLine&);
    int		execute_delete(RequestLine&);
    std::string	path_file(RequestLine&, Server*, Location*);
    std::string	upload_file(std::string, RequestLine &, Location*);
    void		fill_body(std::string);
    void	fill_headers(std::string);
    std::string	    delete_folder_content(std::string ressource);
    std::string chooseIndex(std::vector<std::string>, int flag = -1);
    std::string        list_directory(std::string);
    int                 getError();
    int                 is_cgi();
    std::string         &cgi_path();
    std::string         &cgi_exec();
    ~ResponseFiller();
};


#endif