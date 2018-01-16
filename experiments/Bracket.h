//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_BRACKET_H
#define EXPERIMENTS_BRACKET_H


#include <bitset>
#include "Constants.h"
using namespace std;


class Bracket {
public:
    BracketData data;
    Bracket(BracketData data);
    Bracket* smoothen(Bracket*);
};


#endif //EXPERIMENTS_BRACKET_H
