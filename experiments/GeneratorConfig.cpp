/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/31/17
 */

#include "GeneratorConfig.h"

GeneratorConfig::GeneratorConfig(GroupSelector groupSelector, double retentionP) {
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
    this->intraVariates = GeneratorConfig::getIntraVariates(groupSelector);
    this->retentionP = retentionP;
}

GeneratorConfig::GeneratorConfig(GroupSelector groupSelector, double retentionP, vector<unsigned int> seeds) :
        GeneratorConfig(groupSelector, retentionP) {
    this->seeds = seeds;
}

IntraVariates GeneratorConfig::getIntraVariates(GroupSelector groupSelector) {
    // TODO: get this from a parameter instead of hard-coding the name of the dependency file
    return IntraVariatesUtils::fromFile("../dependency/initial7.txt", groupSelector);
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
