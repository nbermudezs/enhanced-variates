/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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
