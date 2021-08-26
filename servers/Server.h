//
// Created by user on 8/26/2021.
//

#ifndef ASS2_SERVER_H
#define ASS2_SERVER_H

#include "ServerSocket.h"
#include "Classifier.h"
#include "Iris.h"

class Server {
private:
    ServerSocket* serverSocket;
    Classifier<Iris>* classifier;
public:
    Server(ServerSocket* serverSocket, Classifier<Iris>* classifier);

    [[noreturn]] void run();
};


#endif //ASS2_SERVER_H
