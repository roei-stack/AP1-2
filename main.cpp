#include "classifying/Reader.h"
#include "classifying/KnnClassifier.h"
#define K_VALUE 5

/** @param dataset prints the data to the console, will be used for testing purposes. */
void testReading(const vector<Classifiable*>* dataset) {
    int i = 1;
    cout << "*********************************************" << endl << "Reading from classified..." << endl;
    for (Classifiable* c : *dataset) {
        cout << "Line #" << i << " : " << *c << endl;
        i++;
    }
    cout << i - 1 << " Lines read successfully!" << endl << "*********************************************" << endl;
}

/**
 * writes the dataset to an output file
 * @param dataset the dataset
 * @param out the out file
 */
void writeToFile(const vector<Classifiable*>* dataset, ofstream& out) {
    for (Classifiable* c : *dataset) {
        out << *c << endl;
    }
    out.close();
}

/**
 * goes through all unclassified data and applies the classify function
 * @param classifiedData the classified data
 * @param unclassifiedData the unclassified data
 */
void classifyAll(vector<Classifiable*>* classifiedData, vector<Classifiable*>* unclassifiedData) {
    KnnClassifier classifier(K_VALUE, classifiedData);
    for (Classifiable* c: *unclassifiedData) {
        c->setClassification(classifier.classify(*c));
    }
}

/**
 * deletes the vector and it's content.
 * @param toRelease
 */
void release(vector<Classifiable*>* toRelease) {
    for (Classifiable* c : *toRelease) {
        delete c;
    }
    vector<Classifiable*>().swap(*toRelease);
    delete toRelease;
}

int main() {
    string classifiedPath = "..\\classified.csv";
    string unclassifiedPath = "..\\unclassified.csv";
    //// initializing the reader for classified and unclassified
    Reader reader(classifiedPath);
    Reader otherReader(unclassifiedPath);
    //// loading the datasets
    vector<Classifiable*>* classifiedData = reader.buildDataset();
    vector<Classifiable*>* unclassifiedData = otherReader.buildDataset();
    // applying classifier
    classifyAll(classifiedData, unclassifiedData);
    ofstream outFile;
    outFile.open("output.csv");
    writeToFile(unclassifiedData, outFile);
    // releasing
    release(classifiedData);
    release(unclassifiedData);
    return 0;
}
