//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Simulator.h"

Statistics Simulator::run(string &filePath) {
    BracketGenerator generator;
    Bracket* reference = BracketReader::read(filePath);
    for (int i = 0; i < this->runs; i++) {
        GeneratorConfig config;
        Bracket* random = generator.get(false, config, this->setup->variates);
        if (setup->antithetic) {
            Bracket* anti = generator.get(true, config, this->setup->variates);
            Bracket* result = random->smoothen(anti);
            int score = Scorer::eval(reference, result);
            this->stats.accountFor(score, result);
            continue;
        }
        int score = Scorer::eval(reference, random);
        this->stats.accountFor(score, random);
    }

    this->stats.done();

    return this->stats;
}

Simulator::Simulator(SimulatorSetup* setup, int runs) {
    this->setup = setup;
    if (this->setup->antithetic) {
        this->runs = runs / 2;
    } else {
        this->runs = runs;
    }
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates) {
    this->variates = variates;
    for (auto i: variates) {
        if (i == VariateMethod::ANTITHETIC) {
            this->antithetic = true;
            break;
        }
    }
}
