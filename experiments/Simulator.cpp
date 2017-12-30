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

void Simulator::run(string filepath) {
    BracketGenerator generator;
    Bracket* reference = BracketReader::read(filepath);
    for (int i = 0; i < this->runs; i++) {
        Bracket* random = generator.get();
        int score = Scorer::eval(reference, random);
        // TODO: do something with the score
    }

    // TODO: return a class containing the statistics for this run
}
