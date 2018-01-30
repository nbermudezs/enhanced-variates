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
using namespace std;

class Scorer {
public:
    static int naive_eval (BracketData, BracketData);
    static int naive_eval (Bracket *, Bracket *);
    static int eval (BracketData, BracketData);
    static int eval (Bracket *, Bracket *);
    static int evalWithRegionGrouping(BracketData, BracketData);
    static int evalWithRegionGrouping(Bracket *, Bracket *);
    static pair<int, bool> evalRegion(BracketData, BracketData, int);

    // Manhattan distance
    static int l1(BracketData, BracketData);
    static int l1(Bracket *, Bracket *);
    static vector<int> l1ByRounds(BracketData ref, BracketData input);
    static vector<int> l1ByRounds(Bracket *ref, Bracket *input);
};


#endif //EXPERIMENTS_SCORER_H
