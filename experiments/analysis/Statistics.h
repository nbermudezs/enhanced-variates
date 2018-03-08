/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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
#include "../Constants.h"
using namespace std;


class Statistics {
public:
    /**
     * Keeps track of the score and different L1 norms calculated for the given bracket based off the reference bracket
     * of the particular year.
     * @param score The ESPN-based score achieved by the bracket.
     * @param l1s Vector of L1 norms for the different rounds.
     * @param bracket The actual bracket that achieved the score.
     */
    void accountFor(int score, vector<int> l1s, Bracket* bracket);

    void recordFlippedBracket(int scoreDelta, vector<int> l1s, Bracket *bracket);

    /**
     * Marks the tracking of replications as done.
     * Used to avoid some re-computations when possible.
     */
    void done();

    double mean();
    int mode();
    double variance();
    double std();
    int max();
    int min();

    vector<int> topK(size_t, bool);
    vector<int> topQuantile(float, bool);

    /**
     * Creates and returns a table counting how many times each score was achieved.
     * @return Map where the keys are the scores and the values are the number of times that score occurred.
     */
    map<int, int> frequencyTable();

    /**
     * Creates a 2D matrix containing how many times a score occurred with a particular L1 norm.
     * The first key is the L1 norm. L1 norm is calculated using all 62 bits
     * The second key is the ESPN-score
     * The value is the count
     * @return 2D matrix containig the counts
     */
    map<int, map<int, int>> l1DistributionMatrix();

    /**
     * Creates a 2D matrix containing how many times a score occurred with a particular L1 norm.
     * The first key is the L1 norm. L1 norm is calculated using only the bits corresponding to the given round param
     * The second key is the ESPN-score
     * The value is the count
     * @param round Which round of games will be used for the L1 norm.
     * @return 2D matrix containig the counts
     */
    map<int, map<int, int>> l1DistributionMatrix(ROUND round);
    Bracket* bestBracket;
private:
    int bestScore = 0;
    double _mean = -1;
    map<int, int>* _table = nullptr;
    double _variance = -1;

    bool isDone = false;
    vector<int> scores;

    /**
     * Stores the L1 norms for the different rounds
     * The first key of the map is the round (64, 32, 16, 8, 4, 2, ALL)
     * The second key is the actual L1 norm value
     * The vector<int> value keeps track of the different scores obtained with the same norm.
     */
    map<int, map<int, vector<int>>> l1Distances;

    /**
     * Stores the roots of the bracket graphs created by flipping one or more bits
     */
    vector<Bracket*> subGraphs;

    vector<map<int, int>*> scoreDeltas;

    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &ar) {
        // ar(CEREAL_NVP(scores));
        // ar(cereal::make_nvp("mean", mean()));
        // ar(cereal::make_nvp("variance", variance()));
        ar(cereal::make_nvp("max", max()));
        // ar(cereal::make_nvp("min", min()));
        ar(cereal::make_nvp("frequencyTable", frequencyTable()));
        ar(cereal::make_nvp("bestBracket", bestBracket->data.to_string()));

#ifdef CREATE_L1_MATRICES
        for (auto roundPair: RoundNames)
            ar(cereal::make_nvp("l1ScoreMatrix-" + roundPair.second, l1DistributionMatrix(roundPair.first)));
#endif
        // this is only true when we are doing bit flipping.
        if (scoreDeltas.size() > 0)
            for (int i = 0; i < VECTOR_SIZE; i++)
                ar(cereal::make_nvp("scoresDeltaBit" + to_string(i), *scoreDeltas[i]));

#ifdef INCLUDE_BRACKETS_IN_RESULTS
        vector<Bracket> tmp;
        for (int i = 0; i < subGraphs.size(); i++)
            tmp.push_back(*subGraphs[i]);
        ar(cereal::make_nvp("brackets", tmp));
#endif
    }
};


#endif //EXPERIMENTS_STATISTICS_H
