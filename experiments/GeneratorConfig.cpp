//
// Created by Nestor Bermudez Sarmiento on 12/31/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "GeneratorConfig.h"

GeneratorConfig::GeneratorConfig() {
    this->seeds = vector<int>(VECTOR_SIZE);
    for (int i = 0; i < VECTOR_SIZE; i++) {
        this->seeds[i] = abs(rand() * 2 + 1);
    }
    this->antithetic = false;
}

GeneratorConfig::GeneratorConfig(vector<int> seeds, bool antithetic) {
    this->antithetic = antithetic;
    this->seeds = seeds;
}