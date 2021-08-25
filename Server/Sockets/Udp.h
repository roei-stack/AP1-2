//
// Created by User on 23/08/2021.
//

#ifndef ASS2_UDP_H
#define ASS2_UDP_H

#include "SocketStrategy.h"

class Udp : public SocketStrategy{
private:
    int socketId;
    const char* const ip{};
    const int port{};
    struct sockaddr_in sin{};
    bool closed = false;
    const bool isServer;
    struct sockaddr_in from{};
    /**
    * binds the server's ip to it's port
    * bind is server-only operation
    */
    void bind();
public:
    /**
    * constructs a udp connection
    * @param isServer is this instance represents a server or a client, (use defined names - SERVER/CLIENT)
    * @param ip server's ip/ip client will connect to
    * @param port server's port/port client will connect to
    */
    explicit Udp(bool isServer, const char* ip, int port);
    void send(const string& message) const override;
    string receive() override;
    void close() override;
    bool isClosed() const override;
    ~Udp() override;
};

#endif //ASS2_UDP_H
