//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Statistics.h"

void Statistics::accountFor(int score, Bracket*) {
    scores.push_back(score);
}

void Statistics::done() {
    gsl_sort_int(&scores[0], 1, scores.size());
    this->isDone = true;
}

double Statistics::mean() {
    if (isDone) {
        if (_mean == -1) {
            _mean = gsl_stats_int_mean(&scores[0], 1, scores.size());
        }
        return _mean;
    }
    return gsl_stats_int_mean(&scores[0], 1, scores.size());
}

int Statistics::max() {
    if (isDone) {
        return scores.back();
    }
    return *max_element(begin(scores), end(scores));
}

int Statistics::min() {
    if (isDone) {
        return scores.front();
    }
    return *min_element(begin(scores), end(scores));
}

double Statistics::variance() {
    if (isDone) {
        if (_variance == -1) {
            _variance = gsl_stats_int_variance(&scores[0], 1, scores.size());
        }
        return _variance;
    }
    return gsl_stats_int_variance(&scores[0], 1, scores.size());
}

double Statistics::std() {
    return sqrt(variance());
}

vector<int> Statistics::topK(const size_t k, bool unique) {
    vector<int> top(k);
    if (unique) {
        set<int> s(begin(scores), end(scores));
        vector<int> uniqueScores;
        uniqueScores.assign(begin(s), end(s));
        gsl_sort_int_largest(&top[0], k, &uniqueScores[0], 1, uniqueScores.size());
    } else {
        gsl_sort_int_largest(&top[0], k, &scores[0], 1, scores.size());
    }
    return top;
}

vector<int> Statistics::topQuantile(float quantile, bool unique) {
    if (unique) {

    } else {

    }
    return vector<int>();
}

map<int, int> Statistics::frequencyTable() {
    map<int, int> table;
    for (auto score: scores) {
        table[score]++;
    }
    return table;
}
