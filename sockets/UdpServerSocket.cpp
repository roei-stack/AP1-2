//
// Created by user on 8/26/2021.
//

#include "UdpServerSocket.h"

UdpServerSocket::UdpServerSocket(int port, const char *ip) : socket1(nullptr,0, port, ip){

}

Socket* UdpServerSocket::accept() {
    this->socket1.receive();
    this->socket1.send("Udp server ready to receive a message");
    return &this->socket1;
}

void UdpServerSocket::close() {
    this->socket1.close();
}

bool UdpServerSocket::isClosed() const {
    return this->socket1.isClosed();
}

void UdpServerSocket::endCommunicationWithClient() {
    // does nothing
}
