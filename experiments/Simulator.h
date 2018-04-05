/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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
    SimulatorSetup(string dependencyFile, vector<VariateMethod> variates, int year, string format);
    SimulatorSetup(string dependencyFile, vector<VariateMethod> variates, int year, string format, BitFlip flipMode);
    SimulatorSetup(string dependencyFile, vector<VariateMethod> variates, int year, string format, BitFlip flipMode,
                   GenerationDirection generationDirection, GroupSelector groupSelector);
    SimulatorSetup(string dependencyFile, vector<VariateMethod> variates, int year, string format, BitFlip flipMode,
                   GenerationDirection generationDirection, GroupSelector groupSelector, unsigned int masterSeed);
    Bracket* smoothen(Bracket* ref, Bracket* other);

    // attributes
    bool antithetic = false;
    BitFlip flipMode = BitFlip::NO_FLIP;
    GenerationDirection generationDirection;
    string format;
    SmoothingFunction smoothingFunction = SmoothingFunction::AND;
    vector<VariateMethod> variates;
    int year;
    unsigned int masterSeed;
    GroupSelector groupSelector;
    double retentionP;
    string dependencyFile;
};


class Simulator {
public:
    Simulator(SimulatorSetup* setup, int runs, string filePath, bool singleGenerator);
    Statistics run();
    Bracket* reference;
    BracketGenerator generator = BracketGenerator();
    ScoreRanks getScoreRanks() { return this->scoreRanks; }
private:
    bool singleGenerator;
    int runs;
    string bracketFilePath;
    SimulatorSetup* setup;
    Statistics stats;
    ScoreRanks scoreRanks;

    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &ar) {
        ar(CEREAL_NVP(runs));
        ar(CEREAL_NVP(bracketFilePath));
        ar(cereal::make_nvp("masterSeed", setup->masterSeed));
        ar(cereal::make_nvp("flipBits", setup->flipMode));
        ar(cereal::make_nvp("flipBitsName", BitFlipNames[setup->flipMode]));
        ar(cereal::make_nvp("bracket", reference->data.to_string()));
        string groupSelector = setup->groupSelector.to_string();
        reverse(begin(groupSelector), end(groupSelector));
        ar(cereal::make_nvp("rnGroupSelector", groupSelector));

        ar.itsWriter.SetFormatOptions(CEREAL_RAPIDJSON_NAMESPACE::PrettyFormatOptions::kFormatSingleLineArray);
        ar(cereal::make_nvp("variates", setup->variates));
        ar.itsWriter.SetFormatOptions(CEREAL_RAPIDJSON_NAMESPACE::PrettyFormatOptions::kFormatDefault);

        // TODO: once everything uses RandomUtils remove this.
        ar(CEREAL_NVP(singleGenerator));
        // ar(CEREAL_NVP(generator));
        // ar(CEREAL_NVP(RAND_MAX));
    }
};


#endif //EXPERIMENTS_SIMULATOR_H
