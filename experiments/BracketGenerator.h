/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#ifndef EXPERIMENTS_BRACKETGENERATOR_H
#define EXPERIMENTS_BRACKETGENERATOR_H

// serialization
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include <map>
#include <random>
#include "Bracket.h"
#include "cpt/BackwardCPT.h"
#include "cpt/ForwardCPT.h"
#include "cpt/TripletCPT.h"
#include "cpt/MixedCPT.h"
#include "GeneratorConfig.h"
#include "utils/RandomUtils.h"

using namespace std;


class BracketGenerator {
public:
    BracketGenerator() {};
    BracketGenerator(GenerationDirection generationDirection, string format, int year);
    Bracket* get();
    Bracket* get(bool, GeneratorConfig, vector<VariateMethod>);
    Bracket* get(GeneratorConfig config);
    BaseCPT* cpt;
    map<int, int> bitOnCounts;
private:
    minstd_rand0 generator;
    uniform_real_distribution<float> distribution;
    int getMatchResult(BracketData, bool, int, GeneratorConfig, vector<VariateMethod>);

    /**
     * Creates a VECTOR_SIZE-vector of U(0, 1) random numbers.
     * @return the resulting vector.
     */
    vector<double> getRNVector();

    friend class cereal::access;

    template <class Archive>
    void serialize(Archive &ar) {
        ar(CEREAL_NVP(bitOnCounts));
        ar(cereal::make_nvp("cpt", cpt->getUnconditionalProbabilities()));
    }

    TripletCPT *tripletCPT;

    /**
     * Generates a Bracket using the single bit model using the given configuration.
     * @param config Configuration for the generator.
     * @return A bracket
     */
    Bracket* generateWithSingleBits(GeneratorConfig config);

    /**
     * Generates a Bracket using the triplets model using the given configuration.
     * A triplet is formed by a bit, its sibling and the resulting bit in the next round
     * @param config Configuration for the generator.
     * @return A bracket
     */
    Bracket* generateWithTriplets(GeneratorConfig config);
};


#endif //EXPERIMENTS_BRACKETGENERATOR_H
