/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/28/18
 */

#include "MixedCPT.h"

map<string, MixedCPT*> MixedCPT::instances;

int MixedCPT::getParentBit(int bit) {
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

MixedCPT::MixedCPT(string filePath, bool isMetadataFile, int year) {
    this->probabilities.clear();
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
                    int parent = this->getParentBit(bit);
                    conditionalCounts[bit][vector[parent] - '0'] += 1;
                }
            }
        }
        for (unsigned int i = 0; i < VECTOR_SIZE; i++)
            this->probabilities.push_back(1.0 * totalCounts[i] / historyCount);
    }
}

MixedCPT::MixedCPT(string filePath, bool isMetadataFile, int year,
                   map<int, double> overrides):
        MixedCPT(filePath, isMetadataFile, year) {
    this->overrides = overrides;
}

double MixedCPT::P(int matchId) {
    return this->probabilities[matchId];
}

double MixedCPT::P(int matchId, BracketData data) {
    if (this->overrides.find(matchId) != end(this->overrides))
        return this->overrides[matchId];

    if (this->isMetadataFile) {
        return this->P(matchId);
    }
    if (matchId == 62) {
        return 1. * conditionalCounts[matchId][-1] / historyCount;
    }
    if (matchId < 60 && matchId % 15 < 8) {
        return this->P(matchId);
    }
    int parentBit = getParentBit(matchId);
    int parentValue = data[VECTOR_SIZE - parentBit - 1];
    int totalParent = data[parentBit] ? totalCounts[parentBit] : historyCount - totalCounts[parentBit];
    double pParent = 1. * totalParent / historyCount;
    double pJoint = 1. * conditionalCounts[matchId][parentValue] / historyCount;
    return pJoint / pParent;
}

MixedCPT& MixedCPT::getInstance(string path, bool isMetadataFile, int year) {
    static MixedCPT instance(path, isMetadataFile, year);
    return instance;

    // TODO: fix this, we should have a different instance per year
    static map<int, MixedCPT> instances;
    if (instances.find(year) == end(instances)) {
        instances[year] = MixedCPT(path, isMetadataFile, year);
    }
    return instances[year];
}

MixedCPT &
MixedCPT::getInstance(string filePath, bool isMetadataFile, int year, map<int, double> overrides) {
    static MixedCPT instance(filePath, isMetadataFile, year, overrides);
    return instance;
}

MixedCPT &
MixedCPT::getInstance(string filePath, bool isMetadataFile, int year, map<int, double> overrides,
                      string instanceKey) {
    if (!instances[instanceKey]) {
        MixedCPT *instance = new MixedCPT(filePath, isMetadataFile, year, overrides);
        instances[instanceKey] = instance;
    }
    return *instances[instanceKey];
}