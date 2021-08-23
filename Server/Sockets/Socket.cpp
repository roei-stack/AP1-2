//
// Created by User on 23/08/2021.
//

#include "Socket.h"


Socket::Socket(bool isTcpStrategy, bool isServer, const char *ip, int port) {
    if (isTcpStrategy) {
        this->socket = new Tcp(isServer, ip, port);
    } else {
        this->socket = new Udp(isServer, ip, port);
    }
}

void Socket::send(const string &message) const {
    this->socket->send(message);
}

string Socket::receive() {
    return this->socket->receive();
}

void Socket::close() {
    this->socket->close();
}

bool Socket::isClosed() const {
    return this->socket->isClosed();

}

Socket::~Socket() {
    delete this->socket;
}


