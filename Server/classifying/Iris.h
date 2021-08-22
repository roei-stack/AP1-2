//
// Created by user on 7/31/2021.
//

#ifndef ASS1_IRIS_H
#define ASS1_IRIS_H

#include <string>
using namespace std;

class Iris {
private:
    double width;
    double sepalLength;
    double sepalWidth;
    double petalLength;
    string classification;
    void Print(ostream& os) const;
public:
    Iris(double width, double sepalLength, double sepalWidth, double petalLength,
         const string& classification = "");

    string getClassification() const;

    double getDistance(const Iris& other) const;

    void setClassification(const string& newClassification);

    friend ostream& operator<<(ostream& out, const Iris& iris);
};


#endif //ASS1_IRIS_H
