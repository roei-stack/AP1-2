//
// Created by User on 25/08/2021.
//

#include "Sockets/Socket.h"

int main() {
    const char ip[] = "127.0.0.1";
    const int port = 5555;

    Socket tcpServer(TCP, SERVER, ip, port);
    tcpServer.send("CONNECTED!, READY TO RECEIVE MESSAGES!");
    const string input = tcpServer.receive();
    std::cout << "INPUT FROM CLIENT: " << input << std::endl;

    //todo parse input -> tcp/udp input_path output_path
    //todo if tcp -> classify the unclassified, and write to output_path (use the main code from ass1)
    //todo id udp ->
    tcpServer.close();
    return 0;
}