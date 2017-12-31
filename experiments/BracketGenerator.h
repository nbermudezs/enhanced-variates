//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_BRACKETGENERATOR_H
#define EXPERIMENTS_BRACKETGENERATOR_H


#include <random>
#include "Bracket.h"
#include "ConditionalProbabilityTable.h"
#include "GeneratorConfig.h"

using namespace std;


class BracketGenerator {
public:
    BracketGenerator();
    Bracket* get();
    Bracket* get(GeneratorConfig);
    void setSeed(int);
private:
    ConditionalProbabilityTable* cpt;
    default_random_engine generator;
    uniform_real_distribution<float> distribution;
    int getMatchResult(int, GeneratorConfig);
};


#endif //EXPERIMENTS_BRACKETGENERATOR_H
