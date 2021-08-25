//
// Created by User on 23/08/2021.
//

#ifndef ASS2_SOCKETSTRATEGY_H
#define ASS2_SOCKETSTRATEGY_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define BUFFER 2048
// These define result in easier constructor calls
#define CLIENT false
#define SERVER true

using std::string;
using std::runtime_error;

class SocketStrategy {
public:
    /**
    * @param message the message sent to server/client
    */
    virtual void send(const string& message) const = 0;
    /**
     * attempting to read from a socket
     * @return the message inside the socket
     */
    virtual string receive() = 0;
    /**
    * closing socket and it's client, if possible
     */
    virtual void close() = 0;
    /**
     * @return if socket is closed or not
    */
    virtual bool isClosed() const = 0;
    virtual ~SocketStrategy() = default;
};

#endif //ASS2_SOCKETSTRATEGY_H
