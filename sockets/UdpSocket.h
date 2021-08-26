//
// Created by user on 8/26/2021.
//

#ifndef ASS2_UDPSOCKET_H
#define ASS2_UDPSOCKET_H

#include "Socket.h"

class UdpSocket : public Socket {
private:
    bool closed = false;

    int socketId;

    struct sockaddr_in othersin{};
public:
    /**
    * constructs a udp connection
    * @param ip server's ip/ip client will connect to
    * @param port server's port/port client will connect to
    */
    UdpSocket(const char* othersIp, int othersPort);
    explicit UdpSocket(int myPort, const char* myIp = "");
    void send(const string& message) const override;
    string receive() override;
    void close() override;
    bool isClosed() const override;
};


#endif //ASS2_UDPSOCKET_H
