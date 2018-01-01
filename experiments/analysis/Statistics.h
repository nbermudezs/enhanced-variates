//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_STATISTICS_H
#define EXPERIMENTS_STATISTICS_H

// type support for cereal and serialization
#include <cereal/types/bitset.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include <gsl/gsl_sort.h>
#include <gsl/gsl_statistics_int.h>
#include <map>
#include <set>
#include <vector>
#include "../Bracket.h"
using namespace std;


class Statistics {
public:
    void accountFor(int score, Bracket* bracket);
    void done();
    double mean();
    double variance();
    double std();
    int max();
    int min();
    vector<int> topK(size_t, bool);
    vector<int> topQuantile(float, bool);
    map<int, int> frequencyTable();
private:
    double _mean = -1;
    double _variance = -1;
    bool isDone = false;
    vector<int> scores;

    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &ar) {
        // ar(CEREAL_NVP(scores));
        ar(cereal::make_nvp("mean", mean()));
        ar(cereal::make_nvp("variance", variance()));
        ar(cereal::make_nvp("max", max()));
        ar(cereal::make_nvp("min", min()));
        ar(cereal::make_nvp("frequencyTable", frequencyTable()));
    }
};


#endif //EXPERIMENTS_STATISTICS_H
