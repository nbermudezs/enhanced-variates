/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#ifndef EXPERIMENTS_SERIALIZER_H
#define EXPERIMENTS_SERIALIZER_H


#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include "../Constants.h"
#include "../Simulator.h"
#include "../analysis/Statistics.h"
using namespace std;


class Serializer {
public:
    static string getName();
    static string serialize(Simulator simulator, string format, int year);
    static string serialize(Statistics statistics, string format, int year);
    static string serialize(Simulator, Statistics);
    static void serialize(Simulator, Statistics, string);
    static void serialize(Simulator simulator, string format, string filePath);
    static void serialize(Statistics, string format, string filePath);
};


#endif //EXPERIMENTS_SERIALIZER_H
