//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_BRACKETREADER_H
#define EXPERIMENTS_BRACKETREADER_H


#include <string>
#include "Bracket.h"
using namespace std;


class BracketReader {
public:
    Bracket* read(string);
};


#endif //EXPERIMENTS_BRACKETREADER_H
