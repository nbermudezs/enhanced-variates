//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_SERIALIZER_H
#define EXPERIMENTS_SERIALIZER_H


#include <ctime>
#include <fstream>
#include <iomanip>
#include "../Constants.h"
#include "../Simulator.h"
#include "../analysis/Statistics.h"
using namespace std;


class Serializer {
public:
    static void serialize(Simulator, Statistics);
    static void serialize(Simulator, Statistics, string);
};


#endif //EXPERIMENTS_SERIALIZER_H
