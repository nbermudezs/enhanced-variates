/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/31/17
 */

#include "GeneratorConfig.h"

GeneratorConfig::GeneratorConfig() {
    random_device rdev;
    this->seeds = vector<unsigned int>(VECTOR_SIZE);
    for (int i = 0; i < VECTOR_SIZE; i++) {
        const unsigned int seed = rdev();
        this->seeds[i] = seed % 2 == 0 ? seed - 1 : seed;
    }
}

GeneratorConfig::GeneratorConfig(vector<unsigned int> seeds) {
    this->seeds = seeds;
}

void GeneratorConfig::renew(vector<VariateMethod> variates) {
    random_device rdev;
    for (int i = 0; i < VECTOR_SIZE; i++) {
        if (variates[i] == VariateMethod::IID) {
            const unsigned int seed = rdev();
            this->seeds[i] = seed % 2 == 0 ? seed - 1 : seed;
        }
    }
}
