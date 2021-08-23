//
// Created by User on 23/08/2021.
//

#ifndef ASS2_SOCKETSTRATEGY_H
#define ASS2_SOCKETSTRATEGY_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define BUFFER 2048
#define CLIENT false
#define SERVER true

using namespace std;

class SocketStrategy {
public:
    virtual void send(const string& message) const = 0;
    virtual string receive() = 0;
    virtual void close() = 0;
    virtual bool isClosed() const = 0;
};

#endif //ASS2_SOCKETSTRATEGY_H
