//
// Created by Nestor Bermudez Sarmiento on 12/31/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_GENERATORCONFIG_H
#define EXPERIMENTS_GENERATORCONFIG_H


#include <chrono>


class GeneratorConfig {
public:
    GeneratorConfig();
    GeneratorConfig(int, bool);
    int seed;
    bool antithetic;
};


#endif //EXPERIMENTS_GENERATORCONFIG_H
