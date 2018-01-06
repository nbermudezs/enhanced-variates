//
// Created by Nestor Bermudez Sarmiento on 12/29/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Scorer.h"

int Scorer::naive_eval(bitset<VECTOR_SIZE> reference, bitset<VECTOR_SIZE> input) {
    int match_value = 320;

    int score = 0;
    for (int i=0; i < VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15 || i == 31) {
            match_value /= 2;
        }
        if (reference[i] == input[i]) {
            score += match_value;
        }
    }
    return score;
}

int Scorer::eval(bitset<VECTOR_SIZE> reference, bitset<VECTOR_SIZE> input) {
    int match_value = 320;

    int score = 0;
    for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15 || i == 31) {
            match_value /= 2;
        }
        // check previous rounds
        int j = i;
        bool mismatch = false;
        while (j < VECTOR_SIZE) {
            if (reference[j] != input[j]) {
                mismatch = true;
                break;
            }
            int bracketId = (int) floor(log2(j + 1));
            int withinBracketPos = j - pow(2, bracketId) + 1;
            int withinNextBracketPos = withinBracketPos * 2 + 1;
            if (input[j] == 1) {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 1;
            } else {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 2;
            }
        }
        if (!mismatch)
            score += match_value;
    }
    return score;
}

int Scorer::eval(Bracket* ref, Bracket* input) {
    return Scorer::eval(ref->data, input->data);
}

int Scorer::naive_eval(Bracket* ref, Bracket* input) {
    return Scorer::naive_eval(ref->data, input->data);
}