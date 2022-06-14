#ifndef __SELECTIONALGO_HPP__
#define __SELECTIONALGO_HPP__

#include "../Networking/Connections/DataConnection.hpp"
#include "../State/ErrorState.hpp"
#include "../Response/RedirectGenerator.hpp"
#include "../State/SendState.hpp"
#include "../utility/file_utility.hpp"
#include "../ServerConfiguration/Parsing/Components/Components.hpp"
#define IN_SERVER 1
#define IN_LOCATION 2

class SelectionAlgo
{
private:
    Server          *server;
    Location        *location;
    dataConnection  *context;
public:
    SelectionAlgo();
    SelectionAlgo(dataConnection*);
    Server  *getServer();
    Location    *getLocation();
    Return      *checkReturn (int);
    int         default_();
    ~SelectionAlgo();
    
};


#endif