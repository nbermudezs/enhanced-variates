//
// Created by Nestor Bermudez Sarmiento on 12/31/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "GeneratorConfig.h"

GeneratorConfig::GeneratorConfig() {
    this->seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->antithetic = false;
}

GeneratorConfig::GeneratorConfig(int seed, bool antithetic) {
    this->seed = seed;
    this->antithetic = antithetic;
}
