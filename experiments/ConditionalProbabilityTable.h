//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
#define EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H


#include <string>
#include <vector>
#include "Constants.h"
using namespace std;


class ConditionalProbabilityTable {
public:
    ConditionalProbabilityTable();
    ConditionalProbabilityTable(string);
    float P(int);
    vector<float> probabilities;
};


#endif //EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
