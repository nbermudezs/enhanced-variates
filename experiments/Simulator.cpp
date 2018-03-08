/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#include "Simulator.h"

Statistics Simulator::run() {
    GeneratorConfig config(setup->groupSelector, setup->retentionP);
    for (int i = 0; i < this->runs; i++) {
        Bracket* random;
        if (singleGenerator) {
            random = generator.get();
        } else {

            random = generator.get(config);
            // TODO: find a way to support both.
            // GeneratorConfig config;
            // random = generator.get(false, config, this->setup->variates);

            // TODO: make this configurable...
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
        random->setMetadata(l1, score);
        this->stats.accountFor(score, l1, random);

        if (this->setup->flipMode != BitFlip::NO_FLIP) {
            for (int i = 0; i < VECTOR_SIZE; i++) {
                Bracket* flipped = random->flip(i);
                l1 = Scorer::l1ByRounds(reference, flipped);
                int flippedScore = Scorer::evalWithRegionGrouping(reference, flipped);
                flipped->setMetadata(l1, flippedScore);
                random->addChild(flipped);
                this->stats.recordFlippedBracket(flippedScore, l1, flipped);
            }

            if (this->setup->flipMode == BitFlip::TWO_BITS) {
                for (int i = 0; i < VECTOR_SIZE; i++)
                    for (int j = i; j < VECTOR_SIZE; j++) {
                        vector<int> pos = {i, j};

                        Bracket* flipped = random->flip(pos);
                        l1 = Scorer::l1ByRounds(reference, flipped);
                        int flippedScore = Scorer::evalWithRegionGrouping(reference, flipped);
                        flipped->setMetadata(l1, flippedScore);
                        random->addChild(flipped);
                        this->stats.recordFlippedBracket(flippedScore, l1, flipped);
                    }
            }
        }
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
    this->generator = BracketGenerator(setup->generationDirection, setup->format, setup->year);
    this->bracketFilePath = filePath;
    this->reference = BracketReader::readSingle(filePath, setup->year);
    // TODO: replace hardcoded strings
    this->scoreRanks = BracketReader::readESPNScores("brackets/" + setup->format + "/ESPN_scores.json", setup->year);
    this->singleGenerator = singleGenerator;
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates, int year, string format) {
    this->variates = variates;
    this->year = year;
    this->format = format;
    for (auto i: variates) {
        if (i == VariateMethod::ANTITHETIC) {
            this->antithetic = true;
            break;
        }
    }
    this->masterSeed = RandomUtils::generateMasterSeed();
    RandomUtils::setMasterSeed(this->masterSeed);
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates, int year, string format, BitFlip flipMode) :
        SimulatorSetup(variates, year, format) {
    this->flipMode = flipMode;
    this->generationDirection = GenerationDirection::BACKWARD;
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates, int year, string format, BitFlip flipMode,
                               GenerationDirection generationDirection, GroupSelector groupSelector):
        SimulatorSetup(variates, year, format, flipMode) {
    this->generationDirection = generationDirection;
    this->groupSelector = groupSelector;
}

SimulatorSetup::SimulatorSetup(vector<VariateMethod> variates, int year, string format, BitFlip flipMode,
                               GenerationDirection generationDirection, GroupSelector groupSelector, unsigned int masterSeed):
        SimulatorSetup(variates, year, format, flipMode, generationDirection, groupSelector) {
    this->masterSeed = masterSeed;
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
