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

double Iris::getDistance(const Classifiable& other) const {
    const Iris* pI = dynamic_cast<const Iris *>(&other);
    double d = sqrt(
            pow(this->width - pI->width, 2) +
            pow(this->sepalLength - pI->sepalLength, 2) +
            pow(this->sepalWidth - pI->sepalWidth, 2) +
            pow(this->petalLength - pI->petalLength, 2)
            );
    return d;
}

void Iris::setValues(double width, double sepalLength, double sepalWidth, double petalLength,
                      const string &classification) {
    this->width = width;
    this->sepalLength = sepalLength;
    this->sepalWidth = sepalWidth;
    this->petalLength = petalLength;
    this->classification = classification;
}

void Iris::setClassification(string newClassification) {
    this->classification = newClassification;
}

void Iris::Print(ostream &os) const {
    char sep = ',';
    os << this->petalLength << sep << this->sepalWidth << sep <<
    this->sepalLength<< sep<< this->width << sep << this->classification;
}
