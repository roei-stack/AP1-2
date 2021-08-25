//
// Created by User on 25/08/2021.
//

#include "Sockets/Socket.h"

int main() {
    const char ip[] = "127.0.0.1";
    const int port = 7835;

    Socket tcpServer(TCP, SERVER, ip, port);
    tcpServer.send("CONNECTED!, READY TO RECEIVE MESSAGES!");
    const string input = tcpServer.receive();
    //std::cout << "INPUT FROM CLIENT: " << input << std::endl;
    
    
    tcpServer.close();
    return 0;
}
