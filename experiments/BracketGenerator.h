//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_BRACKETGENERATOR_H
#define EXPERIMENTS_BRACKETGENERATOR_H

// serialization
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include <map>
#include <random>
#include "Bracket.h"
#include "ConditionalProbabilityTable.h"
#include "GeneratorConfig.h"

using namespace std;


class BracketGenerator {
public:
    BracketGenerator(int year);
    Bracket* get();
    Bracket* get(bool, GeneratorConfig, vector<VariateMethod>);
    ConditionalProbabilityTable* cpt;
    map<int, int> bitOnCounts;
private:
    minstd_rand0 generator;
    uniform_real_distribution<float> distribution;
    int getMatchResult(BracketData, bool, int, GeneratorConfig, vector<VariateMethod>);

    friend class cereal::access;

    template <class Archive>
    void serialize(Archive &ar) {
        ar(CEREAL_NVP(bitOnCounts));
        ar(cereal::make_nvp("cpt", cpt->probabilities));
    }
};


#endif //EXPERIMENTS_BRACKETGENERATOR_H
