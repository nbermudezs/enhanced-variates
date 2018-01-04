//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_SIMULATOR_H
#define EXPERIMENTS_SIMULATOR_H


// serialization
#include <cereal/archives/json.hpp>

#include "analysis/Statistics.h"
#include "BracketReader.h"
#include "BracketGenerator.h"
#include "Scorer.h"


class SimulatorSetup {
public:
    SimulatorSetup(vector<VariateMethod>);
    vector<VariateMethod> variates;
    bool antithetic;
};


class Simulator {
public:
    Simulator(SimulatorSetup*, int);
    Statistics run(string&);
private:
    int runs;
    SimulatorSetup* setup;
    Statistics stats;

    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &ar) {
        ar(CEREAL_NVP(runs));
        ar(cereal::make_nvp("variates", setup->variates));
    }
};


#endif //EXPERIMENTS_SIMULATOR_H
