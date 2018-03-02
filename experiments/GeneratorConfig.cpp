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
    // TODO: needs to be fixed. The default constructor should not try to read from a file.
    // it should just use all IID instead.
//    IntraVariateGroup allIID;
//    for (int i = 0; i < VECTOR_SIZE; i++) {
//        allIID[VariateMethod::IID].push_back(i);
//    }
//    this->intraVariates = { allIID };
    this->intraVariates = GeneratorConfig::getIntraVariates();
}

GeneratorConfig::GeneratorConfig(vector<unsigned int> seeds) : GeneratorConfig() {
    this->seeds = seeds;
}

IntraVariates GeneratorConfig::getIntraVariates() {
    static IntraVariates intraVariates;
    if (intraVariates.size() == 0) {
        // TODO: change this hardcoded path
        intraVariates = IntraVariatesUtils::fromFile("../dependency/allDeps.txt");
    }
    return intraVariates;
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
