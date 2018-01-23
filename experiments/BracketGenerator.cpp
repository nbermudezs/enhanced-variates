//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

/**
 * For some background on why not use rand:
 * https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
 * http://www.pcg-random.org/posts/cpp-seeding-surprises.html
 *
 * Also for differences between the random generator engines:
 * https://stackoverflow.com/questions/26475595/pseudo-random-number-generator-gives-same-first-output-but-then-behaves-as-expec
 **/

#include "BracketGenerator.h"

BracketGenerator::BracketGenerator(int year) {
    cpt = &ConditionalProbabilityTable::getInstance(BRACKET_METADATA_FOLDER + "/TTT/allBracketsTTT.json", false, year);

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = minstd_rand0(seed);
}

Bracket* BracketGenerator::get() {
    BracketData data;
    for (int matchId = VECTOR_SIZE - 1; matchId >= 0; matchId--) {
        float p = cpt->P(matchId, data);
        int value = distribution(generator) < p ? 1 : 0;
        if (value) {
            bitOnCounts[matchId]++;
        }
        data[VECTOR_SIZE - matchId - 1] = value;
    }
    return new Bracket(data);
}

Bracket *BracketGenerator::get(bool antitheticEnabled, GeneratorConfig config, vector<VariateMethod> variates) {
    BracketData data;
    for (int matchId = VECTOR_SIZE - 1; matchId >= 0; matchId--) {
        int value = getMatchResult(data, antitheticEnabled, matchId, config, variates);
        if (value) {
            bitOnCounts[matchId]++;
        }
        data[matchId] = value;
    }
    return new Bracket(data);
}

int BracketGenerator::getMatchResult(BracketData data, bool antitheticEnabled, int matchId, GeneratorConfig config, vector<VariateMethod> variates) {
    int seed = config.seeds[matchId];
    VariateMethod type = variates[matchId];
    generator = minstd_rand0(seed);

    float p = cpt->P(matchId, data);
    const float rn = type == VariateMethod::ANTITHETIC && antitheticEnabled ?
                     (1 - distribution(generator)) :
                     distribution(generator);
    return rn < p ? 1 : 0;
}
