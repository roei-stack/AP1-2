//
// Created by user on 8/26/2021.
//
#include <string>
#include <iostream>
#include "Socket.h"
#include "UdpSocket.h"
#include "TcpSocket.h"

int main() {
    std::cout << "hey" << std::endl;
    UdpSocket udpSocket("127.0.0.1", 50000);
    std::cout << udpSocket.receive() << std::endl;
    TcpSocket tcpSocket("127.0.0.1", 50001);
    string m = tcpSocket.receive();
    std::cout << m << std::endl;

    Socket* socket;
    string protocol;
    std::cout << "enter the protocol you want to use: (UDP or TCP) " << std::endl;
    std::cin >> protocol;
    while (strcmp(protocol.c_str(), "UDP") != 0 && strcmp(protocol.c_str(), "TCP") != 0) {
        std::cout << "invalid protocol" << std::endl
            <<"enter the protocol you want to use: (UDP or TCP) " << std::endl;
    }
    if (strcmp(protocol.c_str(), "UDP") == 0) {
        socket = &udpSocket;
        tcpSocket.send("cancel");
    } else {
        socket = &tcpSocket;
        udpSocket.send("cancel");
    }

    string unClassifiedPath;
    std::cout << "enter the path of the unclassified file: " << std::endl;
    std::cin >> unClassifiedPath;

    string outputPath;
    std::cout << "enter the path of the output file: " << std::endl;
    std::cin >> outputPath;

    string toSend = unClassifiedPath + "," + outputPath;
    socket->send(toSend);

    std::cout << socket->receive() << std::endl;

    return 0;
}
