/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 4/2/18
 */

#include "TripletCPT.h"

map<string, TripletCPT*> TripletCPT::instances;

TripletCPT::TripletCPT(string filePath, bool isMetadataFile, int year,
                         map<int, double> overrides):
        TripletCPT(filePath, isMetadataFile, year) {
    this->overrides = overrides;
}

TripletCPT::TripletCPT(string filePath, bool isMetadataFile, int year) {
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

        // key1 = bit, key2 = triplet from bit, value = count of triplet occurrences
        auto metrics = map<int, map<int, float>>();
        for (int triplet = 0; triplet < 8; triplet++)
            for (int bit = 0; bit < VECTOR_SIZE; bit++)
                metrics[bit][triplet] = LAPLACE_SMOOTHING;

        for (unsigned int i = 0; i < root.Size(); i++) {
            const CEREAL_RAPIDJSON_NAMESPACE::Value& bracket = root[i]["bracket"];
            int bracketYear = stoi(bracket["year"].GetString());
            // TODO: Use the new CptYearExclusion enum to decide the relation
            if (bracketYear >= year)
                continue;
            historyCount += 1;
            string vector = bracket["fullvector"].GetString();
            for(unsigned int bit = 0; bit < VECTOR_SIZE; bit++) {
                totalCounts[bit] += 1;
                auto parents = this->getParentBits(bit);
                if (parents.first == -1)
                    continue;

                string triplet;
                triplet.append(1, vector[bit]);
                triplet.append(1, vector[parents.first]);
                triplet.append(1, vector[parents.second]);
                metrics[bit][stoi(triplet, nullptr, 2)] += 1;
            }
        }

        // TODO: add some kind of parameter to decide whether to do pooling or not
        auto metricsTmp = map<int, map<int, float>>();
        metricsTmp[61] = metrics[61];
        metricsTmp[62] = metrics[62];
        metricsTmp[63] = metrics[63];
        for (int i = 0; i < REGION_VECTOR_SIZE; i++) {
            for (int regionCtrl = 0; regionCtrl < N_REGIONS; regionCtrl++) {
                for (int region = 0; region < N_REGIONS; region++) {
                    int pos = 15 * region + i;
                    for (int triplet = 0; triplet < 8; triplet++) {
                        metricsTmp[15 * regionCtrl + i][triplet] += metrics[pos][triplet];
                    }
                }
            }
        }

        metrics = metricsTmp;
        for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
            // normalize
            float sum = 0;
            for (int triplet = 0; triplet < metrics[i].size(); triplet++)
                sum += metrics[i][triplet];
            for (int triplet = 0; triplet < metrics[i].size(); triplet++)
                metrics[i][triplet] /= sum;

            // for compatibility with other CPT classes
            this->probabilities.push_back(1.0 * totalCounts[i] / historyCount);
        }
        this->dist = metrics;
    }
}

TripletCPT &TripletCPT::getInstance(string filePath, bool isMetadataFile, int year, map<int, double> overrides,
                                    string instanceKey) {
    if (!instances[instanceKey]) {
        TripletCPT *instance = new TripletCPT(filePath, isMetadataFile, year, overrides);
        instances[instanceKey] = instance;
    }
    return *instances[instanceKey];
}

pair<int, int> TripletCPT::getParentBits(int bitId) {
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

double TripletCPT::P(int bitId) {
    return 0;
}

double TripletCPT::P(int bitId, BracketData data) {
    return 0;
}
