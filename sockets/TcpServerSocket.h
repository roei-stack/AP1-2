//
// Created by user on 8/26/2021.
//

#ifndef ASS2_TCPSERVERSOCKET_H
#define ASS2_TCPSERVERSOCKET_H


#include "ServerSocket.h"
#include "TcpSocket.h"

class TcpServerSocket : public ServerSocket {
private:
    bool closed = false;
    int socketId;

    TcpSocket clientSocket;
public:
    explicit TcpServerSocket(int port, const char* ip = "");

    Socket* accept() override;

    void endCommunicationWithClient() override;

    void close() override;

    bool isClosed() const override;
};


#endif //ASS2_TCPSERVERSOCKET_H
