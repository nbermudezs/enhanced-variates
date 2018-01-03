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
        Bracket* random = generator.get(config);
        int score = Scorer::eval(reference, random);
        this->stats.accountFor(score, random);
    }

    this->stats.done();

    return this->stats;
}

Simulator::Simulator(SimulatorSetup* setup, int runs) {
    this->runs = runs;
    this->setup = setup;
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates) {
    this->variates = variates;
}
