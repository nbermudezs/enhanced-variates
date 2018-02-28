/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/7/18
 */

#include "ForwardCPT.h"

map<string, ForwardCPT*> ForwardCPT::instances;

ForwardCPT::ForwardCPT(string filePath, bool isMetadataFile, int year) {
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

        /* stupid initialization because C++ does not have an equivalent to defaultdict */
        vector<pair<int, int>> pairs = { make_pair(-1, -1), make_pair(0, 0), make_pair(0, 1), make_pair(1, 0), make_pair(1, 1) };
        for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
            for (auto p: pairs) {
                this->conditionalCounts[i][p] = 1;
                this->parentCounts[i][p] = 1;
            }
        }

        for (unsigned int i = 0; i < root.Size(); i++) {
            const CEREAL_RAPIDJSON_NAMESPACE::Value &bracket = root[i]["bracket"];
            int bracketYear = stoi(bracket["year"].GetString());
            if (bracketYear == year)
                continue;
            string vector = bracket["fullvector"].GetString();
            for (unsigned int bit = 0; bit < VECTOR_SIZE; bit++) {
                int sibling = this->getSiblingBit(bit);
                pair<int, int> thisPairValues;
                if (sibling > bit)
                    thisPairValues = make_pair(vector[bit] - '0', vector[sibling] - '0');
                else
                    thisPairValues = make_pair(vector[sibling] - '0', vector[bit] - '0');
                if (bit < 60 && bit % 15 < 8) {
                    if (vector[bit] - '0' == 1)
                        this->parentCounts[bit][make_pair(-1, -1)] += 1;
                } else {
                    this->parentCounts[bit][thisPairValues] += 1;
                }

                pair<int, int> parents = this->getParentBits(bit);
                pair<int, int> parentValues = make_pair(vector[parents.first] - '0', vector[parents.second] - '0');

                if (vector[bit] - '0' == 1)
                    this->conditionalCounts[bit][parentValues] += 1;
            }
        }
    }
}

double ForwardCPT::P(int bitId) {
    if (this->overrides[bitId])
        return this->overrides[bitId];
    return this->probabilities[bitId];
}

double ForwardCPT::P(int bitId, BracketData data) {
    if (this->overrides[bitId])
        return this->overrides[bitId];

    if (this->isMetadataFile)
        return this->P(bitId);


    pair<int, int> parents = this->getParentBits(bitId);
    if (parents.first < 0)
        return 1. * this->parentCounts[bitId][parents] / YEARS;
    pair<int, int> values = make_pair(data[VECTOR_SIZE - parents.first - 1], data[VECTOR_SIZE - parents.second - 1]);
    int count = this->conditionalCounts[bitId][values];
    int parentsCount = this->parentCounts[parents.first][values];
    return 1. * count / parentsCount;
}

/* PRIVATE */
pair<int, int> ForwardCPT::getParentBits(int bitId) {
    if (bitId == 62) return make_pair(60, 61);
    if (bitId == 61) return make_pair(44, 59);
    if (bitId == 60) return make_pair(14, 29);
    if (bitId % 15 < 8) return make_pair(-1, -1);

    int mod = bitId % 15;
    if (mod == 14) return make_pair(bitId - 2, bitId - 1);

    int factor = bitId / 15;
    int base;
    if (mod < 12) base = (mod % 8) * 2 + 15 * factor;
    else if (mod < 14) base = 8 + (mod % 12) * 2 + 14 * factor;
    return make_pair(base, base + 1);
}

int ForwardCPT::getSiblingBit(int bitId) {
    if (bitId == 62) return -1;
    if (bitId == 60) return 61;
    if (bitId == 14) return 29;
    if (bitId == 29) return 14;
    if (bitId == 44) return 60;
    if (bitId == 59) return 44;
    int delta = (bitId % 15) % 2 == 0 ? 1 : -1;
    return bitId + delta;
}

ForwardCPT &ForwardCPT::getInstance(string filePath, bool isMetadataFile, int year, map<int, double> overrides,
                                    string instanceKey) {
    if (!instances[instanceKey]) {
        ForwardCPT *instance = new ForwardCPT(filePath, isMetadataFile, year, overrides);
        instances[instanceKey] = instance;
    }
    return *instances[instanceKey];
}
