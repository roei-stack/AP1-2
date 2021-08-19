//
// Created by user on 7/31/2021.
//

#ifndef ASS1_IRIS_H
#define ASS1_IRIS_H


#include "Classifiable.h"
#include <string>
using namespace std;

class Iris : public Classifiable {
private:
    double width;
    double sepalLength;
    double sepalWidth;
    double petalLength;
    string classification;
    void Print(ostream& os) const override;
public:
    Iris(double width, double sepalLength, double sepalWidth, double petalLength,
         const string& classification = "");

    string getClassification() const override;

    double getDistance(const Classifiable& other) const override;

    void setValues(double width, double sepalLength, double sepalWidth, double petalLength,
                           const string& classification) override;

    void setClassification(string newClassification) override;
};


#endif //ASS1_IRIS_H
