//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
#define EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H

#include <cmath>
#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/istreamwrapper.h>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Constants.h"
using namespace std;

const int YEARS = 33;


class ConditionalProbabilityTable {
public:
    ConditionalProbabilityTable();
    ConditionalProbabilityTable(string, bool, int);
    double P(int);
    double P(int, BracketData);
    vector<float> probabilities;
    int historyCount = 0;
    map<int, map<int, int>> conditionalCounts; // { "bit0": { "parent-0": a, "parent-1": b }, ... }
    map<int, int> totalCounts;
    static ConditionalProbabilityTable& getInstance(string, bool, int);

private:
    bool isMetadataFile;
};


#endif //EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
