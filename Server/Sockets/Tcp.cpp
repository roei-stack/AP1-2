//
// Created by User on 22/08/2021.
//

#include "Tcp.h"

Tcp::Tcp(bool isServer, const char* const ip, const int port): ip(ip), port(port){
    // getting socket
    this->socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketId < 0) {
        throw runtime_error("error creating socket");
    }
    // by default, client sends using its own socket id, and servers will create a unique client socket
    this->clientSock = socketId;
    // server : bind, listen, accept...
    if (isServer) {
        this->bind();
        this->listen();
        this->accept();
        return;
    }
    //client : connect...
    this->connect();
}

// bind is server-only operation
void Tcp::bind() {
    memset(&sin, 0, sizeof(sin));
    this->sin.sin_family = AF_INET;
    if (strcmp(ip, "0.0.0.0") != 0 || strcmp(ip, "") != 0) {
        this->sin.sin_addr.s_addr = INADDR_ANY;
    } else {
        this->sin.sin_addr.s_addr = inet_addr(this->ip);
    }
    this->sin.sin_port = htons(this->port);
    if (::bind(this->socketId, (struct sockaddr *) &this->sin, sizeof(this->sin)) < 0) {
        throw runtime_error("error binding socket");
    }
}

// listen is a server's only operation
void Tcp::listen() const {
    int size = 5;
    if (::listen(this->socketId, size) < 0) {
        throw runtime_error("error listening to a socket");
    }
}

// accept is used by server's
void Tcp::accept() {
    // closing the connection with previous client
    this->attemptToCloseClient();
    unsigned int address_len = sizeof(this->clientSin);
    this->clientSock = ::accept(this->socketId, (struct sockaddr *) &this->clientSin,  &address_len);
    if (this->clientSock < 0) {
        throw runtime_error("error accepting client");
    }
}

// connect is used by clients trying to connect to servers
void Tcp::connect() {
    memset(&sin, 0, sizeof(this->sin));
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(this->ip);
    this->sin.sin_port = htons(this->port);
    if (::connect(this->socketId, (struct sockaddr *) &this->sin, sizeof(this->sin)) < 0) {
        throw runtime_error("connection failed");
    }
}

void Tcp::send(const string& message) const {
    long bytesSent = ::send(this->clientSock, message.c_str(), BUFFER, 0);
    if (bytesSent < 0) {
        throw runtime_error("error sending, connection may be closed");
    }
}

string Tcp::receive() {
    char buffer[BUFFER];
    long bytesRead = ::recv(this->clientSock, buffer, BUFFER, 0);
    if (bytesRead == 0) {
        // connection is closed
        ::close(this->socketId);
        this->attemptToCloseClient();
    }
    else if (bytesRead < 0) {
        throw runtime_error("failed receiving the message");
    }
    // buffer holds the message
    string str(buffer);
    return str;
}

void Tcp::attemptToCloseClient() {
    if (!this->isClientClosed && (this->socketId != this->clientSock)) {
        this->isClientClosed = true;
        ::close(this->clientSock);
    }
}

void Tcp::close() {
    this->closed = true;
    ::close(this->socketId);
    this->attemptToCloseClient();
}

bool Tcp::isClosed() const {
    return this->closed;
}

Tcp::~Tcp() {
    if (!this->closed) {
        ::close(this->socketId);
    }
    this->attemptToCloseClient();
}
