//
// Created by Nestor Bermudez Sarmiento on 1/24/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_MISC_H
#define EXPERIMENTS_MISC_H

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
};


#endif //EXPERIMENTS_MISC_H
