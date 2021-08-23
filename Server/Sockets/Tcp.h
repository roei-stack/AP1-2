//
// Created by User on 22/08/2021.
//

#ifndef ASS2_TCP_H
#define ASS2_TCP_H

#include "SocketStrategy.h"

class Tcp : public SocketStrategy{
private:
    int socketId;
    // for servers- it's the ip and port to bind to, for client's, it's their local ip
    const char* const ip{};
    const int port{};
    struct sockaddr_in sin{};
    bool closed = false;
    // the accepted client's info
    struct sockaddr_in clientSin{};
    int clientSock;
    bool isClientClosed = false;

    void attemptToCloseClient();
    void bind();
    void listen() const;
    void accept();
    void connect();
public:
    explicit Tcp(bool isServer, const char* ip, int port);
    void send(const string& message) const override;
    string receive() override;
    void close() override;
    bool isClosed() const override;
    ~Tcp();
};

#endif //ASS2_TCP_H
