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
    // server will : bind, listen, accept...
    if (isServer) {
        this->bind();
        this->listen();
        this->accept();
        return;
    }
    //client will : connect...
    this->connect();
}

void Tcp::bind() {
    // initializing sin
    memset(&sin, 0, sizeof(sin));
    this->sin.sin_family = AF_INET;
    // addresses "0.0.0.0" and empty strings are translated to ANY_ADDRESS
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

void Tcp::listen() const {
    int size = 5;
    if (::listen(this->socketId, size) < 0) {
        throw runtime_error("error listening to a socket");
    }
}

void Tcp::accept() {
    // closing the connection with previous client
    this->attemptToCloseClient();
    // waiting on next client
    unsigned int address_len = sizeof(this->clientSin);
    this->clientSock = ::accept(this->socketId, (struct sockaddr *) &this->clientSin,  &address_len);
    if (this->clientSock < 0) {
        throw runtime_error("error accepting client");
    }
}

void Tcp::connect() {
    // initializing sin to avoid garbage value errors
    memset(&sin, 0, sizeof(this->sin));
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(this->ip);
    this->sin.sin_port = htons(this->port);
    // attempting to connect
    if (::connect(this->socketId, (struct sockaddr *) &this->sin, sizeof(this->sin)) < 0) {
        throw runtime_error("connection failed");
    }
}

void Tcp::send(const string& message) const {
    /*
     * if this instance is a server, it will use the client socket to communicate with the client
     * if this instance is a client, then: clientSock = SocketId
     */
    long bytesSent = ::send(this->clientSock, message.c_str(), message.size(), 0);
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
    // converting to string type
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
