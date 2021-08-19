//
// Created by User on 02/08/2021.
//

#include "KnnClassifier.h"
#include <algorithm>
#include <map>

KnnClassifier::KnnClassifier(const int k, vector<Classifiable *> *dataset): k(k), dataset(dataset) {
    votesMapping["Iris-setosa"] = 0;
    votesMapping["Iris-versicolor"] = 0;
    votesMapping["Iris-virginica"] = 0;
}

string KnnClassifier::classify(const Classifiable& c) {
    // sorting the data set according to the distance from c
    class ClassifiablesComparatorByDistToClassifiable {
    private:
        const Classifiable& classifiable;
    public:
        explicit ClassifiablesComparatorByDistToClassifiable(const Classifiable& c) : classifiable(c) {}

        bool operator() (const Classifiable* c1,const Classifiable* c2) {
            return classifiable.getDistance(*c1) < classifiable.getDistance(*c2);
        }
    };
    ClassifiablesComparatorByDistToClassifiable cmp(c);
    nth_element(this->dataset->begin(), this->dataset->begin() + k, this->dataset->end(), cmp);
    return this->chooseBestClassification();
}

string KnnClassifier::chooseBestClassification() {
    int index = 0;
    pair<string, int> maxPair("", 0);
    for (Classifiable *current : *this->dataset) {
        if (index == this->k) {
            break;
        }
        for (auto& item : votesMapping)
        {
            //item.first is the string key, item.second => it's int value
            if (current->getClassification() == item.first) {
                item.second++;
                if (maxPair.second < item.second) {
                    maxPair = item;
                }
            }
        }
        index++;
    }
    this->resetMap();
    return maxPair.first;
}

void KnnClassifier::resetMap() {
    for (auto& item : this->votesMapping) {
        item.second = 0;
    }
}
