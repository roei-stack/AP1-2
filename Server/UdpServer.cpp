//
// Created by User on 25/08/2021.
//
#include "Sockets/Socket.h"

int main() {
    const char ip[] = "127.0.0.1";
    const int port = 5555;

    Socket udpServer(UDP, SERVER, ip, port);

    udpServer.close();
    return 0;
}
