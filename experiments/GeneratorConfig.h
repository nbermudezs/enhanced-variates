/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/31/17
 */

#ifndef EXPERIMENTS_GENERATORCONFIG_H
#define EXPERIMENTS_GENERATORCONFIG_H


#include <cstdlib>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>
#include "Constants.h"
#include "variates/IntraVariates.h"
using namespace std;


class GeneratorConfig {
public:
    GeneratorConfig();
    GeneratorConfig(vector<unsigned int>);
    vector<unsigned int> seeds;
    void renew(vector<VariateMethod> variates);
    IntraVariates intraVariates;
private:
    static IntraVariates getIntraVariates();
};


#endif //EXPERIMENTS_GENERATORCONFIG_H
