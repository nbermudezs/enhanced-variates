//
// Created by Nestor Bermudez Sarmiento on 12/29/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Scorer.h"

int Scorer::naive_eval(BracketData reference, BracketData input) {
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

int Scorer::eval(BracketData reference, BracketData input) {
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

int Scorer::evalWithRegionGrouping(Bracket* ref, Bracket* input) {
    return Scorer::evalWithRegionGrouping(ref->data, input->data);
}

int Scorer::evalWithRegionGrouping(BracketData ref, BracketData input) {
    int matchValue = 320;

    pair<int, bool> south = Scorer::evalRegion(ref, input, 48);
    pair<int, bool> west = Scorer::evalRegion(ref, input, 33);
    pair<int, bool> east = Scorer::evalRegion(ref, input, 18);
    pair<int, bool> midwest = Scorer::evalRegion(ref, input, 3);

    int score = south.first + west.first + east.first + midwest.first;

    // check semifinals
    if (ref[2] == input[2]) {
        if (ref[2] == 1 && south.second || ref[2] == 0 && west.second) {
            score += 160;

            // check championship
            if (ref[0] == input[0] && ref[0] == 1) {
                score += 320;
            }
        }
    }

    if (ref[1] == input[1]) {
        if (ref[1] == 1 && east.second || ref[1] == 0 && midwest.second) {
            score += 160;

            // check championship
            if (ref[0] == input[0] && ref[0] == 0) {
                score += 320;
            }
        }
    }

    return score;
}

pair<int, bool> Scorer::evalRegion(BracketData reference, BracketData input, int offset) {
    int matchValue = 80;
    bool finalsMatch = false;

    int score = 0;
    for (unsigned int i = 0; i < REGION_VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15) {
            matchValue /= 2;
        }
        // check previous rounds
        int j = i;
        bool mismatch = false;
        while (j < REGION_VECTOR_SIZE) {
            if (reference[j + offset] != input[j + offset]) {
                mismatch = true;
                break;
            }
            int bracketId = (int) floor(log2(j + 1));
            int withinBracketPos = j - pow(2, bracketId) + 1;
            int withinNextBracketPos = withinBracketPos * 2 + 1;
            if (input[j + offset] == 1) {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 1;
            } else {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 2;
            }
        }
        if (!mismatch) {
            score += matchValue;
            if (i == 0) {
                finalsMatch = true;
            }
        }
    }
    return pair<int, bool>(score, finalsMatch);
}

int Scorer::l1(BracketData ref, BracketData input) {
    int count = 0;
    for (unsigned int i = 0; i < VECTOR_SIZE; i++)
        count += abs(ref[i] - input[i]);
    return count;
}

int Scorer::l1(Bracket* ref, Bracket* input) {
    return Scorer::l1(ref->data, input->data);
}