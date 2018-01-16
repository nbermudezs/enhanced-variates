//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Simulator.h"

Statistics Simulator::run() {
    for (int i = 0; i < this->runs; i++) {
        Bracket* random;
        if (singleGenerator) {
            random = generator.get();
        } else {
            GeneratorConfig config;
            random = generator.get(false, config, this->setup->variates);

            if (setup->antithetic) {
                config.renew(this->setup->variates);
                Bracket* anti = generator.get(true, config, this->setup->variates);
                Bracket* result = this->setup->smoothen(random, anti);
                vector<Bracket*> brackets = { random, anti, result };
                Bracket* best;
                int bestScore = 0;
                for (Bracket* bracket: brackets) {
                    int score = Scorer::eval(reference, bracket);
                    if (bestScore < score) {
                        bestScore = score;
                        best = bracket;
                    }
                }
                this->stats.accountFor(bestScore, best);
                this->stats.accountFor(Scorer::eval(reference, random), random);
                this->stats.accountFor(Scorer::eval(reference, anti), anti);
                // this->stats.accountFor(Scorer::eval(reference, result), result);
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
    if (this->setup->antithetic && !singleGenerator) {
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

Bracket *SimulatorSetup::smoothen(Bracket *ref, Bracket *other) {
    BracketData smoothenData;
    std::function<float(float, float)> fn;
    switch (smoothingFunction) {
        case SmoothingFunction::XOR:
            fn = [](int bit_a, int bit_b) { return 1. * (bit_a ^ bit_b); };
            break;
        case SmoothingFunction::OR:
            fn = [](int bit_a, int bit_b) { return 1. * (bit_a | bit_b); };
            break;
        case SmoothingFunction::AVG:
            fn = [](int bit_a, int bit_b) { return (bit_a + bit_b) / 2.; };
            break;
        default:
            fn = [](int bit_a, int bit_b) { return 1. * (bit_a & bit_b); };
    }
    for (int i = 0; i < VECTOR_SIZE; i++) {
        smoothenData[i] = fn(ref->data[i], other->data[i]);
    }
    return new Bracket(smoothenData);
}
