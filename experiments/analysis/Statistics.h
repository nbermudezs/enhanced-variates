//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_STATISTICS_H
#define EXPERIMENTS_STATISTICS_H


#include <vector>
#include "../Bracket.h"
using namespace std;


class Statistics {
public:
    void accountFor(int score, Bracket* bracket);
    float mean();
    int max();
private:
    vector<int> scores;
};


#endif //EXPERIMENTS_STATISTICS_H
