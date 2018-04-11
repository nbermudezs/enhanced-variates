/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/29/17
 */

#ifndef EXPERIMENTS_SCORER_H
#define EXPERIMENTS_SCORER_H

#include <cmath>
#include <iostream>
#include <vector>
#include "Bracket.h"
#include "utils/BracketUtils.h"
using namespace std;

class Scorer {
public:
    static int naive_eval (BracketData, BracketData);
    static int naive_eval (Bracket *, Bracket *);
    static int eval (BracketData, BracketData);
    static int eval (Bracket *, Bracket *);
    static int evalWithRegionGrouping(BracketData, BracketData);
    static int evalWithRegionGrouping(Bracket *, Bracket *);
    static int evalFFF(Bracket *ref, Bracket *input);

    /**
     * Calculates the score of a bracket given a reference bracket
     * It returns a vector containing the score achieved on each of the rounds.
     * There are 6 rounds but the vector size is 7. The last element in the vector is the total score.
     * @param ref Bracket used as reference (ground truth)
     * @param input Bracket to be evaluated against the reference
     * @return Score total and per round
     */
    static vector<int> byRound(BracketData ref, BracketData input);
    static vector<int> byRound(Bracket *ref, Bracket *input);

    static pair<int, bool> evalRegion(BracketData, BracketData, int);

    /**
     * Calculates the score, broken down by round, for the specific region within a bracket
     * @param ref Bracket used as reference (ground truth)
     * @param input Bracket to be evaluated against the reference
     * @param offset Indicates where the region starts within the bracket
     * @return Score per round of that region
     */
    static pair<vector<int>, bool> scoreRegion(BracketData ref, BracketData input, int offset);

    // Manhattan distance
    static int l1(BracketData, BracketData);
    static int l1(Bracket *, Bracket *);
    static vector<int> l1ByRounds(BracketData ref, BracketData input);
    static vector<int> l1ByRounds(Bracket *ref, Bracket *input);
};


#endif //EXPERIMENTS_SCORER_H
