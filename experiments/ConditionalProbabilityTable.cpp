//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "ConditionalProbabilityTable.h"

// TODO: default to probability 0.5 instead of the hardcoded value in ConditionalProbabilityTable::P
ConditionalProbabilityTable::ConditionalProbabilityTable() {

}

// TODO: load probability table from a file (result of Ian's data)
ConditionalProbabilityTable::ConditionalProbabilityTable(string filepath) {

}

float ConditionalProbabilityTable::P(int matchId) {
    return 0.5;
    if (matchId >= 32) {
        return 0.5;
    }
    // seed 1
    if (matchId % 8 == 0) {
        return 1;
    }
    // seed 2
    if (matchId % 8 == 7) {
        return 0.939;
    }
    // seed 3
    if (matchId % 8 == 5) {
        return 0.841;
    }
    // seed 4
    if (matchId % 8 == 3) {
        return 0.803;
    }
    // seed 5
    if (matchId % 8 == 2) {
        return 0.644;
    }
    // seed 6
    if (matchId % 8 == 4) {
        return 0.629;
    }
    // seed 7
    if (matchId % 8 == 6) {
        return 0.614;
    }
    // seed 8
    if (matchId % 8 == 1) {
        return 0.508;
    }
}
