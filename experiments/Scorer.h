//
// Created by Nestor Bermudez Sarmiento on 12/29/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_SCORER_H
#define EXPERIMENTS_SCORER_H

#include <iostream>
#include <vector>
#include "Bracket.h"
using namespace std;

class Scorer {
public:
    static int eval (vector<int>, vector<int>);
    static int eval (Bracket *, Bracket *);
};


#endif //EXPERIMENTS_SCORER_H
