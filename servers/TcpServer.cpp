//
// Created by user on 8/26/2021.
//

#include "Reader.h"
#include <string>
#include "KnnClassifier.h"
#include "TcpServerSocket.h"
#include "Server.h"

using std::string;

int main() {
    string classifiedPath = "../classification/classified.csv";
    //// initializing the reader for classified and unclassified
    Reader reader(classifiedPath);
    //// loading the datasets
    vector<Iris*>* classifiedData = reader.buildDataset();
    //// creating classifier
    KnnClassifier<Iris> classifier(5, classifiedData);

    //// creating the socket
    TcpServerSocket serverSocket(50001);

    //// creating the server
    Server server(&serverSocket, &classifier);
    //// running the server
    server.run();

    return 0;
}