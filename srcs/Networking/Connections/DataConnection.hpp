#ifndef __DATA_CONNECTION_HPP__
#define __DATA_CONNECTION_HPP__

#include <string>

#include "Connection.hpp"
#include "../../Request/Request.hpp"
#include "../Activity/Activity.hpp"
#include "../../Response/Response.hpp"
#include "../../OutputBuffer/OutputBuffer.hpp"
#include "../../InputBuffer/InputBuffer.hpp"

class State;

/*****************************************************
 *	handles the actual exchange of data betweeen 
 * 	the server and the client at the other end
 * 	- input: a buffer for the input data from fd
 *	- activity: records last time this connection has 
 *				used.
 *	- request:	request from the client
 * 	- response: response to send to client
 * 	- state: state design pattern to handle the state
 * 			at which the connection is on.
 *	- event: API with ConnectionHandler for READ/WRITE
 *			events.
 *	- close: is true the ConnectionHandler must delete
 *			this connection
 * **************************************************/

class dataConnection: public Connection {
    private:
		OutputBuffer	*outputBuffer;
		InputBuffer		*inputBuffer;
		Activity        *activity;
        Request         *request;
        Response        *response;
        State           *state;
        bool            close;
    public:
        dataConnection (int fd);
        ~dataConnection ();
        InputBuffer& getInputBuffer ();
		OutputBuffer& getOutputBuffer ();
		Request *getRequest ();
        void    setResponse (Response *);
        Response *getResponse ();
        void TranslationTo (State *);
		Activity& getActivity ();
        bool getClose ();
        void setClose ();
		void SetState (State *);
        bool isClose () const;
        void handle ();
};
#endif