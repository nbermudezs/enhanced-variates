//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "BracketGenerator.h"

BracketGenerator::BracketGenerator() {
    cpt = new ConditionalProbabilityTable();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = default_random_engine(seed);
}


Bracket* BracketGenerator::get() {
    bitset<VECTOR_SIZE> data;
    for (int matchId = 0; matchId < VECTOR_SIZE; matchId++) {
        float p = cpt->P(matchId);
        data[matchId] = distribution(generator) < p ? 1 : 0;
    }
    return new Bracket(data);
}
