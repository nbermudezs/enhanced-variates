//
// Created by Nestor Bermudez Sarmiento on 12/31/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_GENERATORCONFIG_H
#define EXPERIMENTS_GENERATORCONFIG_H


#include <cstdlib>
#include <chrono>
#include <vector>
#include "Constants.h"
using namespace std;


class GeneratorConfig {
public:
    GeneratorConfig();
    GeneratorConfig(vector<int>, bool);
    bool antithetic;
    vector<int> seeds;
};


#endif //EXPERIMENTS_GENERATORCONFIG_H
