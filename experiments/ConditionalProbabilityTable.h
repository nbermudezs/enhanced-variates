//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
#define EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H

#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/istreamwrapper.h>
#include <fstream>
#include <string>
#include <vector>
#include "Constants.h"
using namespace std;

const int YEARS = 33;


class ConditionalProbabilityTable {
public:
    ConditionalProbabilityTable();
    ConditionalProbabilityTable(string);
    float P(int);
    vector<float> probabilities;
    static ConditionalProbabilityTable& getInstance(string);
};


#endif //EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
