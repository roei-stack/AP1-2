//
// Created by user on 8/26/2021.
//

#ifndef ASS2_TCPSOCKET_H
#define ASS2_TCPSOCKET_H


#include "Socket.h"

class TcpSocket : public Socket {
private:
    bool closed = false;

    int socketId;
public:
    explicit TcpSocket(int socketId);
    TcpSocket(const char* othersIp, int othersPort);
    void send(const string& message) const override;
    string receive() override;
    void close() override;
    bool isClosed() const override;
};


#endif //ASS2_TCPSOCKET_H
