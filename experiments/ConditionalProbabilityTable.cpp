//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "ConditionalProbabilityTable.h"

// TODO: default to probability 0.5 instead of the hardcoded value in ConditionalProbabilityTable::P
ConditionalProbabilityTable::ConditionalProbabilityTable() {
    for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
        this->probabilities.push_back(0.5);
    }
}

ConditionalProbabilityTable::ConditionalProbabilityTable(string filePath) {
    ifstream file(filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);
    const CEREAL_RAPIDJSON_NAMESPACE::Value& array = d["sumOfBrackets"];
    assert(array.IsArray());
    for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
        if (i < 32)
            this->probabilities.push_back(1.0 * array[i].GetInt() / YEARS);
        else
            this->probabilities.push_back(0.5);
    }
}

float ConditionalProbabilityTable::P(int matchId) {
    return this->probabilities[matchId];
}

ConditionalProbabilityTable& ConditionalProbabilityTable::getInstance(string path) {
    static ConditionalProbabilityTable instance(path);
    return instance;
}
