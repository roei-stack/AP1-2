//
// Created by User on 25/08/2021.
//
#include "Server/Sockets/Socket.h"

int main() {
    // connecting to tcp server and sending the input message
    const char ip[] = "127.0.0.1";
    const int port = 5555;
    std::string input;
    Socket client(TCP, CLIENT, ip, port);
    std::cout << "SERVER: " << client.receive() << std::endl;
    std::getline(std::cin, input);
    client.send(input);
    // closing client after sending message
    client.close();
    return 0;
}
