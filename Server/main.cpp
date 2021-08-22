#include <iostream>
#include "classifying/Reader.h"
#include "classifying/KnnClassifier.h"

#define K_VALUE 5

/** @param dataset prints the data to the console, will be used for testing purposes. */
void testReading(const vector<Iris*>* dataset) {
    int i = 1;
    cout << "*********************************************" << endl << "Reading from classified..." << endl;
    for (Iris* iris : *dataset) {
        cout << "Line #" << i << " : " << *iris << endl;
        i++;
    }
    cout << i - 1 << " Lines read successfully!" << endl << "*********************************************" << endl;
}

/**
 * writes the dataset to an output file, and closes out after that.
 * @param dataset the dataset
 * @param out the out file
 */
void writeToFile(const vector<Iris*>* dataset, ofstream& out) {
    for (Iris* iris : *dataset) {
        out << *iris << endl;
    }
    out.close();
}

/**
 * goes through all unclassified data and applies the classify function
 * @param classifiedData the classified data
 * @param unclassifiedData the unclassified data
 */
void classifyAll(vector<Iris*>* classifiedData, vector<Iris*>* unclassifiedData) {
    KnnClassifier<Iris> classifier(K_VALUE, classifiedData);
    for (Iris* iris: *unclassifiedData) {
        iris->setClassification(classifier.classify(*iris));
    }
}

/**
 * deletes the vector and it's content.
 * @param toRelease
 */
void release(vector<Iris*>* toRelease) {
    for (Iris* iris : *toRelease) {
        delete iris;
    }
    vector<Iris*>().swap(*toRelease);
    delete toRelease;
}

int main() {
    string classifiedPath = "..\\Server\\classified.csv";
    string unclassifiedPath = "..\\Server\\Unclassified.csv";
    //// initializing the reader for classified and unclassified
    Reader reader(classifiedPath);
    Reader otherReader(unclassifiedPath);
    //// loading the datasets
    vector<Iris*>* classifiedData = reader.buildDataset();
    vector<Iris*>* unclassifiedData = otherReader.buildDataset();

    testReading(classifiedData);
    testReading(unclassifiedData);
    //// applying classifier
    classifyAll(classifiedData, unclassifiedData);
    ofstream outFile;
    outFile.open("..\\output.csv");
    writeToFile(unclassifiedData, outFile);
    //// releasing data
    release(classifiedData);
    release(unclassifiedData);

    return 0;
}
