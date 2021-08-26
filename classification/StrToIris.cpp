//
// Created by user on 8/26/2021.
//

#include "StrToIris.h"

static Iris convert(string& str) {
    double petalLength, sepalWidth, sepalLength, width;
    string type;
    //"petal length,sepal width, sepal length, width"
    // array of 4 arguments, all initialized to empty string
    stringstream values[5];
    values[4] = stringstream("");
    stringstream check(str);
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
    Iris iris(width, sepalLength, sepalWidth,petalLength, type);
    return iris;
}
