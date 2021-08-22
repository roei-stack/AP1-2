//
// Created by User on 02/08/2021.
//

#ifndef ASS1_CLASSIFIER_H
#define ASS1_CLASSIFIER_H

template<class T>
class Classifier {
public:
    /**
     * returns the classification of c
     * @param c to classify. c must be an appropriate Classifiable such that
     *     c knows how to calculate the distance from the Classifiables in this Classifier's dataset.
     *     probably, c will have to be from the same type as them.
     *     **if other's type won't be appropriate, an exception may be thrown.**
     * @return string
     */
    virtual string classify(const T& toClassify) = 0;

    /**
     * virtual destructor.
     */
    virtual ~Classifier() = default;
};

#endif //ASS1_CLASSIFIER_H
