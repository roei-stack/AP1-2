//
// Created by user on 8/26/2021.
//

#ifndef ASS2_SERVERSOCKET_H
#define ASS2_SERVERSOCKET_H

#include "Socket.h"

using std::string;

class ServerSocket {
public:

    /**
     * accepts a client.
     * @return int, the socket id to talk with the client from.
     */
    virtual Socket* accept() = 0;

    /**
     * ends the communication with the current client.
     */
    virtual void endCommunicationWithClient() = 0;

    /**
    * closing the socket
     */
    virtual void close() = 0;

    /**
     * @return if socket is closed or not
    */
    virtual bool isClosed() const = 0;

    virtual ~ServerSocket() = default;
};

#endif //ASS2_SERVERSOCKET_H
