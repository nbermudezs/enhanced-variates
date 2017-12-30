//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_SIMULATOR_H
#define EXPERIMENTS_SIMULATOR_H


#include "analysis/Statistics.h"
#include "BracketReader.h"
#include "BracketGenerator.h"
#include "Scorer.h"


class Simulator {
public:
    Simulator();
    Simulator(int);
    Statistics run(string);
private:
    int runs;
    Statistics stats;
};


#endif //EXPERIMENTS_SIMULATOR_H
