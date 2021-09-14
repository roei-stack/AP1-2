//
// Created by user on 8/26/2021.
//

#include "Server.h"
#include "Reader.h"
#include <string>
#include <sstream>

Server::Server(ServerSocket *serverSocket, Classifier<Iris>* classifier) {
    this->serverSocket = serverSocket;
    this->classifier = classifier;
}

/**
 * deletes the vector and it's content.
 * @param toRelease
 */
void release(vector<Iris*>* toRelease) {
    for (Iris* c : *toRelease) {
        delete c;
    }
    vector<Iris*>().swap(*toRelease);
    delete toRelease;
}

/**
 * writes the dataset to an output file
 * @param dataset the dataset
 * @param out the out file
 */
void writeToFile(const vector<Iris*>* dataset, ofstream& out) {
    for (Iris* c : *dataset) {
        out << *c << endl;
    }
}

[[noreturn]] void Server::run() {
    while (true) {
        Socket* clientSocket = serverSocket->accept();
        string paths = clientSocket->receive();
        if (!(paths == "cancel")) {
            try {
                string unclassifiedPath, outputPath;

                istringstream ss(paths);
                char delim = ',';
                getline(ss, unclassifiedPath, delim);
                getline(ss, outputPath, delim);

                // reading
                Reader reader(unclassifiedPath);
                vector<Iris*>* unclassifiedData = reader.buildDataset();
                // classifying
                for (Iris* iris : *unclassifiedData) {
                    iris->setClassification(this->classifier->classify(*iris));
                }
                // writing
                ofstream outFile;
                outFile.open(outputPath);
                writeToFile(unclassifiedData, outFile);
                outFile.close();
                // releasing
                release(unclassifiedData);

                clientSocket->send("finished classifying");
            } catch (...) {
                clientSocket->send("an error occurred");
            }
        }
        //ending the communication with the client
        this->serverSocket->endCommunicationWithClient();
    }
}
