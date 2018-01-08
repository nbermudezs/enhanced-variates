//
// Created by Nestor Bermudez Sarmiento on 12/31/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "GeneratorConfig.h"

GeneratorConfig::GeneratorConfig() {
    random_device rdev;
    this->seeds = vector<int>(VECTOR_SIZE);
    for (int i = 0; i < VECTOR_SIZE; i++) {
        this->seeds[i] = rdev() * 2 + 1;
    }
}

GeneratorConfig::GeneratorConfig(vector<int> seeds) {
    this->seeds = seeds;
}