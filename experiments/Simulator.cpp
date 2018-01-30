/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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
                    int score = Scorer::evalWithRegionGrouping(reference, bracket);
                    if (bestScore < score) {
                        bestScore = score;
                        best = bracket;
                    }
                }
                this->stats.accountFor(bestScore, vector<int>(), best);
                this->stats.accountFor(Scorer::eval(reference, random), vector<int>(), random);
                this->stats.accountFor(Scorer::eval(reference, anti), vector<int>(), anti);
                // this->stats.accountFor(Scorer::eval(reference, result), result);
                continue;
            }
        }
        // TODO: figure out how to do antithetic with a single generator
        int score = Scorer::evalWithRegionGrouping(reference, random);
        vector<int> l1 = Scorer::l1ByRounds(reference, random);
        this->stats.accountFor(score, l1, random);
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
    this->generator = BracketGenerator(setup->year);
    this->bracketFilePath = filePath;
    this->reference = BracketReader::readSingle(filePath, setup->year);
    this->singleGenerator = singleGenerator;
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates, int year) {
    this->variates = variates;
    this->year = year;
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
        smoothenData[i] = fn(ref->data[i], other->data[i]) > 0;
    }
    return new Bracket(smoothenData);
}
