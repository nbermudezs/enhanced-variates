//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "ConditionalProbabilityTable.h"

int getParentBit(int bit) {
    int parent;
    if (bit == 14 || bit == 29)
        parent = 60;
    else if (bit == 44 || bit == 59)
        parent = 61;
    else if (bit == 60 || bit == 61)
        parent = 62;
    else {
        int relBit = bit % 15;
        int regionId = bit / 15;
        if (relBit >= 0 && relBit < 8) {
            parent = regionId * 15 + 8 + (int) floor(relBit / 2);
        } else if (relBit >= 8 && relBit < 12) {
            parent = regionId * 15 + 12 + (int) floor((relBit - 8) / 2);
        } else {
            parent = regionId * 15 + 14;
        }
    }
    return parent;
}

// TODO: default to probability 0.5 instead of the hardcoded value in ConditionalProbabilityTable::P
ConditionalProbabilityTable::ConditionalProbabilityTable() {
    for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
        this->probabilities.push_back(0.5);
    }
}

ConditionalProbabilityTable::ConditionalProbabilityTable(string filePath, bool isMetadataFile, int year) {
    this->isMetadataFile = isMetadataFile;

    ifstream file(filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);

    if (isMetadataFile) {
        const CEREAL_RAPIDJSON_NAMESPACE::Value& array = d["sumOfBrackets"];
        assert(array.IsArray());
        for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
            this->probabilities.push_back(1.0 * array[i].GetFloat() / YEARS);
        }
    } else {
        const CEREAL_RAPIDJSON_NAMESPACE::Value& root = d["brackets"];
        assert(root.IsArray());
        for (unsigned int i = 0; i < root.Size(); i++) {
            const CEREAL_RAPIDJSON_NAMESPACE::Value& bracket = root[i]["bracket"];
            int bracketYear = stoi(bracket["year"].GetString());
            if (bracketYear == year)
                continue;
            historyCount += 1;
            string vector = bracket["fullvector"].GetString();
            for(unsigned int bit = 0; bit < VECTOR_SIZE; bit++) {
                if (vector[bit] == '0')
                    continue;
                totalCounts[bit] += 1;
                if (bit == VECTOR_SIZE - 1) {
                    conditionalCounts[bit][-1] += 1;
                } else {
                    int parent = getParentBit(bit);
                    conditionalCounts[bit][vector[parent] - '0'] += 1;
                }
            }
        }
    }
}

double ConditionalProbabilityTable::P(int matchId) {
    return this->probabilities[matchId];
}

double ConditionalProbabilityTable::P(int matchId, BracketData data) {
    if (this->isMetadataFile) {
        return this->P(matchId);
    }
    if (matchId == 62) {
        return 1. * conditionalCounts[matchId][-1] / historyCount;
    }
    int parentBit = getParentBit(matchId);
    int parentValue = data[VECTOR_SIZE - parentBit - 1];
    int totalParent = data[parentBit] ? totalCounts[parentBit] : historyCount - totalCounts[parentBit];
    double pParent = 1. * totalParent / historyCount;
    double pJoint = 1. * conditionalCounts[matchId][parentValue] / historyCount;
    return pJoint / pParent;
}

ConditionalProbabilityTable& ConditionalProbabilityTable::getInstance(string path, bool isMetadataFile, int year) {
    static ConditionalProbabilityTable instance(path, isMetadataFile, year);
    return instance;

    // TODO: fix this, we should have a different instance per year
    static map<int, ConditionalProbabilityTable> instances;
    if (instances.find(year) == end(instances)) {
        instances[year] = ConditionalProbabilityTable(path, isMetadataFile, year);
    }
    return instances[year];
}
