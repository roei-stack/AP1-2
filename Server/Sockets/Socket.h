//
// Created by User on 23/08/2021.
//

#ifndef ASS2_SOCKET_H
#define ASS2_SOCKET_H

#include "SocketStrategy.h"
#include "Tcp.h"
#include "Udp.h"
#define TCP true
#define UDP false

// using the strategy design pattern
class Socket {
private:
    SocketStrategy* socket;
public:
    /**
    * constructs a socket connection
    * EXAMPLE:: Socket s(TCP,SERVER,"127.0.0.1",5555) - will create a tcp server on local ip with port 5555
    * @param isTcpStrategy the connection's type (use defined names such as TCP and UDP)
    * @param isServer is this instance represents a server or a client, (use defined names - SERVER/CLIENT)
    * @param ip server's ip/ip client will connect to
    * @param port server's port/port client will connect to
    */
    explicit Socket(bool isTcpStrategy, bool isServer, const char* ip, int port);
    void send(const string& message) const;
    string receive();
    void close();
    bool isClosed() const;
    ~Socket();
};

#endif //ASS2_SOCKET_H
