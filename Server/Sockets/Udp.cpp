//
// Created by User on 23/08/2021.
//

#include "Udp.h"

Udp::Udp(bool isServer, const char* const ip, int port): isServer(isServer), ip(ip), port(port) {
    // getting a socket
    this->socketId = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->socketId < 0) {
        throw runtime_error("error creating socket");
    }
    // initialize sin
    memset(&this->sin, 0, sizeof(this->sin));
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(this->ip);
    this->sin.sin_port = htons(this->port);
    // server ip addresses such as "0.0.0.0" and empty will convert to "address_any"
    if (isServer) {
        if (strcmp(ip, "0.0.0.0") != 0 || strcmp(ip, "") != 0) {
            this->sin.sin_addr.s_addr = INADDR_ANY;
        }
        this->bind();
    }
}

void Udp::bind() {
    if (::bind(this->socketId, (struct sockaddr *) &this->sin, sizeof(this->sin)) < 0) {
        throw runtime_error("error binding to socket");
    }
}

void Udp::send(const string &message) const {
    long bytesSent;
    // the message is sent differently based on if we are a client or a server
    if (this->isServer) {
        bytesSent = sendto(socketId, message.c_str(), message.size(), 0, (struct sockaddr *) &from, sizeof(from));
    } else {
        bytesSent = sendto(socketId, message.c_str(), message.size(), 0, (struct sockaddr *) &sin, sizeof(sin));
    }
    if (bytesSent < 0) {
        throw runtime_error("error sending to socket");
    }
}

string Udp::receive() {
    unsigned int fromLen = sizeof(struct sockaddr_in);
    char buffer[BUFFER];
    long bytes = recvfrom(this->socketId, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &fromLen);
    if (bytes < 0) {
        throw runtime_error("error reading from socket");
    }
    string str(buffer);
    return str;
}

void Udp::close() {
    if (!this->closed) {
        this->closed = true;
        ::close(this->socketId);
    }
}

bool Udp::isClosed() const {
    return this->closed;
}

Udp::~Udp() {
    if (!this->isClosed()) {
        ::close(this->socketId);
    }
}
