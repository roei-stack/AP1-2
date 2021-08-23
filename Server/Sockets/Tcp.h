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

    /**
    * closing the client socket if it's open
    */
    void attemptToCloseClient();
    /**
    * binds the server's ip to it's port
    * bind is server-only operation
    */
    void bind();
    /**
    * default queue size is 5
    * listen is a server's only operation
    */
    void listen() const;
    /**
     * removing current client and accepting/waiting for next client
     * accept is used by server's only
     */
    void accept();
    /**
    * connect is used by clients trying to connect to servers
    */
    void connect();
public:
    /**
    * constructs a tcp connection
    * @param isServer is this instance represents a server or a client (use defined names - SERVER/CLIENT)
    * @param ip server's ip/ip client will connect to
    * @param port server's port/port client will connect to
    */
    explicit Tcp(bool isServer, const char* ip, int port);
    void send(const string& message) const override;
    string receive() override;
    void close() override;
    bool isClosed() const override;
    ~Tcp() override;
};

#endif //ASS2_TCP_H
