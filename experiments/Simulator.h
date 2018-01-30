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
    SimulatorSetup(vector<VariateMethod>, int);
    vector<VariateMethod> variates;
    bool antithetic = false;
    Bracket* smoothen(Bracket* ref, Bracket* other);
    SmoothingFunction smoothingFunction = SmoothingFunction::AND;
    int year;
};


class Simulator {
public:
    Simulator(SimulatorSetup*, int, string, bool);
    Statistics run();
    Bracket* reference;
    BracketGenerator generator = BracketGenerator(0);
private:
    bool singleGenerator;
    int runs;
    string bracketFilePath;
    SimulatorSetup* setup;
    Statistics stats;

    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &ar) {
        ar(CEREAL_NVP(runs));
        ar(CEREAL_NVP(bracketFilePath));
        ar(cereal::make_nvp("bracket", reference->data.to_string()));

        auto transformVariate = [](VariateMethod x) { return ENUM_NAME(x); };
        vector<string> variates(VECTOR_SIZE);
        transform(begin(setup->variates), end(setup->variates), begin(variates), transformVariate);

        ar(cereal::make_nvp("variates", variates));
        ar(CEREAL_NVP(singleGenerator));
        ar(CEREAL_NVP(generator));
        ar(CEREAL_NVP(RAND_MAX));
        ar(cereal::make_nvp("smoothingFunction", ENUM_NAME(setup->smoothingFunction)));
    }
};


#endif //EXPERIMENTS_SIMULATOR_H
