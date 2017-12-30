//
// Created by Nestor Bermudez Sarmiento on 12/29/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Scorer.h"

int Scorer::eval(vector<int> ref, vector<int> input) {
    vector<int>::size_type size = ref.size();
    int match_value = 10;

    int score = 0;
    for (unsigned i=0; i < size; i++) {
        if (i == 32 || i == 48 || i == 56 || i == 60 || i == 62 || i == 63) {
            match_value *= 2;
        }
        if (ref[i] == input[i]) {
            score += match_value;
        }
    }
    return score;
}

int Scorer::eval(Bracket* ref, Bracket* input) {
    return Scorer::eval(ref->data, input->data);
}
