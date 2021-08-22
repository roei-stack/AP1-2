//
// Created by user on 7/31/2021.
//

#include "Iris.h"
#include <cmath>
#include <iostream>

Iris::Iris(double width, double sepalLength, double sepalWidth, double petalLength,
           const string& classification) {
    this->width = width;
    this->sepalLength = sepalLength;
    this->sepalWidth = sepalWidth;
    this->petalLength = petalLength;
    this->classification = classification;
}

string Iris::getClassification() const {
    return this->classification;
}

double Iris::getDistance(const Iris& other) const {
    double d = sqrt(
            pow(this->width - other.width, 2) +
            pow(this->sepalLength - other.sepalLength, 2) +
            pow(this->sepalWidth - other.sepalWidth, 2) +
            pow(this->petalLength - other.petalLength, 2)
            );
    return d;
}

void Iris::setClassification(const string& newClassification) {
    this->classification = newClassification;
}

void Iris::Print(ostream &os) const {
    char sep = ',';
    os << this->petalLength << sep << this->sepalWidth << sep <<
    this->sepalLength<< sep<< this->width << sep << this->classification;
}

ostream& operator<<(ostream& out, const Iris& iris) {
    iris.Print(out);
    return out;
}
