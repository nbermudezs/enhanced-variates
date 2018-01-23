//
// Created by Nestor Bermudez Sarmiento on 12/29/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

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
};


#endif //EXPERIMENTS_SCORER_H
