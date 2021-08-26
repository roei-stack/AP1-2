//
// Created by user on 8/26/2021.
//

#include "TcpServerSocket.h"

TcpServerSocket::TcpServerSocket(int port, const char *ip) : clientSocket(-1){
    this->socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketId < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    if (strcmp(ip, "") != 0) {
        sin.sin_addr.s_addr = inet_addr(ip);
    } else {
        sin.sin_addr.s_addr = INADDR_ANY;
    }
    sin.sin_port = htons(port);

    if (bind(this->socketId, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    if (listen(this->socketId, 5) < 0) {
        perror("error listening to a socket");
    }
}

Socket *TcpServerSocket::accept() {
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = ::accept(this->socketId,  (struct sockaddr *) &client_sin,  &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }

    this->clientSocket = TcpSocket(client_sock);

    this->clientSocket.send("Tcp Server ready to receive message");

    return &this->clientSocket;
}

void TcpServerSocket::close() {
    ::close(this->socketId);
    this->closed = true;
}

bool TcpServerSocket::isClosed() const {
    return this->closed;
}

void TcpServerSocket::endCommunicationWithClient() {
    this->clientSocket.close();
}
