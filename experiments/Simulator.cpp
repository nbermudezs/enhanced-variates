//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Simulator.h"

Statistics Simulator::run() {
    BracketGenerator generator;
    for (int i = 0; i < this->runs; i++) {
        Bracket* random;
        if (singleGenerator) {
            random = generator.get();
        } else {
            GeneratorConfig config;
            random = generator.get(false, config, this->setup->variates);

            if (setup->antithetic) {
                Bracket* anti = generator.get(true, config, this->setup->variates);
                Bracket* result = random->smoothen(anti);
                int score = Scorer::eval(reference, result);
                this->stats.accountFor(score, result);
                continue;
            }
        }
        // TODO: figure out how to do antithetic with a single generator
        int score = Scorer::eval(reference, random);
        this->stats.accountFor(score, random);
    }

    this->stats.done();

    return this->stats;
}

Simulator::Simulator(SimulatorSetup* setup, int runs, string filePath, bool singleGenerator) {
    this->setup = setup;
    if (this->setup->antithetic) {
        this->runs = runs / 2;
    } else {
        this->runs = runs;
    }
    this->bracketFilePath = filePath;
    this->reference = BracketReader::read(filePath);
    this->singleGenerator = singleGenerator;
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
