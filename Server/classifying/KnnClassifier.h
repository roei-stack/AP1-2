//
// Created by User on 02/08/2021.
//

#ifndef ASS1_KNNCLASSIFIER_H
#define ASS1_KNNCLASSIFIER_H

#include "Classifier.h"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

/**
 * knn classifier.
 *
 * @tparam T is a classifiable - it has the following methods:
 *     1. double getDistance(T other)
 *     2. string getClassification()
 */
template<class T>
class KnnClassifier : public Classifier<T> {
private:
    const int k;
    vector<T*>* dataset;

    string chooseBestClassification();
public:
    /**
     * constructor.
     * @param k the k of knn
     * @param dataset the dataset. *this classifier doesn't delete it when deleted itself*.
     */
    KnnClassifier(int k, vector<T*>* dataset);

    /**
    * returns the classification of toClassify
    * @param toClassify T is a classifiable - it has the following methods:
     *     1. double getDistance(T other)
     *     2. string getClassification()
    * @return string
    */
    string classify(const T& toClassify) override;
};

template<class T>
KnnClassifier<T>::KnnClassifier(const int k, vector<T*> *dataset) : k(k) {
    this->dataset = dataset;
}

template<class T>
string KnnClassifier<T>::classify(const T& toClassify) {
    // sorting the data set according to the distance from toClassify
    class TComparatorByDistToToClassify {
    private:
        const T& toClassify;
    public:
        explicit TComparatorByDistToToClassify(const T& toClassify) : toClassify(toClassify) {}

        bool operator() (const T* t1,const T* t2) {
            return toClassify.getDistance(*t1) < toClassify.getDistance(*t2);
        }
    };
    TComparatorByDistToToClassify cmp(toClassify);
    nth_element(this->dataset->begin(), this->dataset->begin() + k, this->dataset->end(), cmp);
    // choosing the classification
    return this->chooseBestClassification();
}

template<class T>
string KnnClassifier<T>::chooseBestClassification() {
    // voteMap will map classifications to the number of close neighbors that have them.
    map<string, int> votesMap;
    // maxPair will be the classification from voteMap with the highest value.
    pair<string, int> maxPair("", 0);

    int index = 0;
    for (T *current : *this->dataset) {
        // we need only the first k
        if (index == this->k) {
            break;
        }
        index++;

        string classification = current->getClassification();
        // updating votesMap
        if (votesMap.count(classification) == 0) {
            votesMap[classification] = 1;
        } else {
            votesMap[classification]++;
        }
        // updating maxPair after the change in the votesMap
        auto it = votesMap.find(classification);
        if (it->second > maxPair.second) {
            maxPair = *it;
        }
    }

    return maxPair.first;
}

#endif //ASS1_KNNCLASSIFIER_H
