//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Simulator.h"

Simulator::Simulator() {
    this->runs = 1e6;
}

Simulator::Simulator(int runs) {
    this->runs = runs;
}

Statistics Simulator::run(string filePath) {
    BracketGenerator generator;
    Bracket* reference = BracketReader::read(filePath);
    for (int i = 0; i < this->runs; i++) {
        Bracket* random = generator.get();
        int score = Scorer::eval(reference, random);
        this->stats.accountFor(score, random);
    }

    return this->stats;
}
