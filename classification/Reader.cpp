#include "Reader.h"
#include <iostream>
#include <sstream>

/**
 * @param filePath the path to the input file
 */
Reader::Reader(const string& filePath) {
    this->file.open(filePath);
    // taking care of bad inputs
    if (!this->file.is_open()) {
        throw invalid_argument("Failed to initialize file reader at path " + filePath);
    }
}

/**
 * builds the database from the csv file
 * @return a vector-list of pointers to heap-allocated Iris objects
 */
vector<Iris*>* Reader::buildDataset() {
    vector<Iris *> *data;
    data = new vector<Iris *>;

    string line;
    while (this->file >> line) {
        Iris* iris = parseLine(line);
        data->push_back(iris);
    }
    // Requests the container to reduce its capacity to fit its size, so no memory is wasted
    data->shrink_to_fit();

    // closing the file as we finished using it
    this->close();

    return data;
}

/**
 * translates a string line into an object
 * @param line the given line
 * @return a pointer to classified object
 * remember to free the database
 */
Iris* Reader::parseLine(const string& line) {
    double petalLength, sepalWidth, sepalLength, width;
    string type;
    //"petal length,sepal width, sepal length, width"
    // array of 4 arguments, all initialized to empty string
    stringstream values[5];
    values[4] = stringstream("");
    stringstream check(line);
    string current;
    int i = 0;
    char delim = ',';
    while(getline(check, current, delim)) {
        values[i] << current;
        i++;
    }
    // assigning values
    values[0] >> petalLength;
    values[1] >> sepalWidth;
    values[2] >> sepalLength;
    values[3] >> width;
    values[4] >> type;
    // creating the object
    Iris* iris = new Iris(width, sepalLength, sepalWidth,petalLength, type);
    return iris;
}

/**
 * closes the file
 */
void Reader::close() {
    this->file.close();
}
