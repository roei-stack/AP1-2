//
// Created by user on 8/26/2021.
//

#include "UdpSocket.h"

UdpSocket::UdpSocket(const char * const othersIp, int othersPort) {
    this->socketId = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->socketId < 0) {
        perror("error creating socket");
    }

    memset(&this->othersin, 0, sizeof(this->othersin));
    this->othersin.sin_family = AF_INET;
    this->othersin.sin_addr.s_addr = inet_addr(othersIp);
    this->othersin.sin_port = htons(othersPort);
}

UdpSocket::UdpSocket(const char *othersIp, int othersPort, int myPort, const char *myIp) {
    this->socketId = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->socketId < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    if (strcmp(myIp, "") != 0) {
        sin.sin_addr.s_addr = inet_addr(myIp);
    } else {
        sin.sin_addr.s_addr = INADDR_ANY;
    }
    sin.sin_port = htons(myPort);
    if (bind(this->socketId, (struct sockaddr *) &sin, sizeof(sin)) < 0){
        perror("error binding to socket");
    }

    memset(&this->othersin, 0, sizeof(this->othersin));
    this->othersin.sin_family = AF_INET;
    this->othersin.sin_addr.s_addr = inet_addr(othersIp);
    this->othersin.sin_port = htons(othersPort);
}

void UdpSocket::send(const string &message) const {
    long bytesSent = sendto(socketId, message.c_str(), message.size(),
                            0, (struct sockaddr *) &this->othersin, sizeof(this->othersin));
    if (bytesSent < 0) {
        perror("error sending message");
    }
}

string UdpSocket::receive() {
    unsigned int fromLen = sizeof(struct sockaddr_in);
    char buffer[BUFFER];
    long bytes = recvfrom(this->socketId, buffer, sizeof(buffer),
                         0, (struct sockaddr *) &this->othersin, &fromLen);
    if (bytes < 0) {
        throw runtime_error("error reading from socket");
    }
    string str(buffer);
    return str;
}

void UdpSocket::close() {
    if (!this->closed) {
        ::close(this->socketId);
        this->closed = true;
    }
}

bool UdpSocket::isClosed() const {
    return this->closed;
}
