/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/24/18
 */

#ifndef EXPERIMENTS_MISC_H
#define EXPERIMENTS_MISC_H

#include "../cpt/ConditionalProbabilityTable.h"
#include "../Constants.h"
#include "../Scorer.h"

#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/istreamwrapper.h>
#include <fstream>
#include <map>
#include <string>
using namespace std;

class Misc {
public:
    static map<int, map<int, int>> l1Matrix(string filePath);
    static map<int, map<int, double>> conditionalProbabilityMatrix(string filePath, int year);
};


#endif //EXPERIMENTS_MISC_H
