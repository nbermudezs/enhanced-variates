/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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
    ConditionalProbabilityTable(string filePath, bool isMetadataFile, int year);
    ConditionalProbabilityTable(string filePath, bool isMetadataFile, int year, map<int, double> overrides);
    double P(int);
    double P(int, BracketData);
    vector<double> probabilities;
    int historyCount = 0;
    map<int, map<int, int>> conditionalCounts; // { "bit0": { "parent-0": a, "parent-1": b }, ... }
    map<int, int> totalCounts;
    static ConditionalProbabilityTable& getInstance(string, bool, int);
    static ConditionalProbabilityTable& getInstance(string filePath, bool isMetadataFile, int year,
                                                    map<int, double> overrides);
    static ConditionalProbabilityTable& getInstance(string filePath, bool isMetadataFile, int year,
                                                    map<int, double> overrides, string instanceKey);

private:
    bool isMetadataFile;
    map<int, double> overrides;
    static map<string, ConditionalProbabilityTable*> instances;
};


#endif //EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
