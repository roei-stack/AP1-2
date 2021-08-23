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
    void bind();
public:
    explicit Udp(bool isServer, const char* ip, int port);
    void send(const string& message) const override;
    string receive() override;
    void close() override;
    bool isClosed() const override;
    ~Udp();
};


#endif //ASS2_UDP_H
