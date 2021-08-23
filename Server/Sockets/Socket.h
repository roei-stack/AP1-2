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

class Socket {
private:
    SocketStrategy* socket;
public:
    explicit Socket(bool isTcpStrategy, bool isServer, const char* ip, int port);
    void send(const string& message) const;
    string receive();
    void close();
    bool isClosed() const;
    ~Socket();
};


#endif //ASS2_SOCKET_H
