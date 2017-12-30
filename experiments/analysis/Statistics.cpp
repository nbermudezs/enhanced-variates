//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Statistics.h"

void Statistics::accountFor(int score, Bracket *bracket) {
    scores.push_back(score);
}

float Statistics::mean() {
    return gsl_stats_int_mean(&scores[0], 1, scores.size());
}

int Statistics::max() {
    return *max_element(begin(scores), end(scores));
}

float Statistics::variance() {
    return gsl_stats_int_variance(&scores[0], 1, scores.size());
}

float Statistics::std() {
    return gsl_stats_int_sd(&scores[0], 1, scores.size());
}
