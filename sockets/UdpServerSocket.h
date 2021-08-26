//
// Created by user on 8/26/2021.
//

#ifndef ASS2_UDPSERVERSOCKET_H
#define ASS2_UDPSERVERSOCKET_H

#include "ServerSocket.h"
#include "UdpSocket.h"

class UdpServerSocket : public ServerSocket {
private:
    UdpSocket socket1;
public:
    explicit UdpServerSocket(int port, const char* ip = "");

    Socket* accept() override;

    void endCommunicationWithClient() override;

    void close() override;

    bool isClosed() const override;

};


#endif //ASS2_UDPSERVERSOCKET_H
