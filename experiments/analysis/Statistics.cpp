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
    float sum = 0.0;
    int count = 0;
    for (auto const score: scores) {
        sum += score;
        count += 1;
    }
    return sum / count;
}

int Statistics::max() {
    return *max_element(begin(scores), end(scores));
}
