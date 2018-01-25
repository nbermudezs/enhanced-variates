//
// Created by Nestor Bermudez Sarmiento on 1/24/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_PRINTUTILS_H
#define EXPERIMENTS_PRINTUTILS_H

#include <map>
#include <vector>
#include "../Constants.h"
#include "../analysis/Statistics.h"

ostream &operator<<(ostream &os, vector<int> &v) {
    for(auto &i: v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

ostream &operator<<(ostream &os, map<int, int> &table) {
    os << "|------|------|" << endl;
    for (auto &it: table) {
        os << "|" << setw(6) << it.first << "|" << setw(6) << it.second << "|" << endl;
    }
    os << " ------------- " << endl;
    return os;
}

ostream &operator<<(ostream &os, BracketData data) {
    os << data.to_string();
    return os;
}

ostream &operator<<(ostream &os, Bracket* bracket) {
    os << bracket->data;
    return os;
}

void printFrequencyTable(ostream &os, map<int, int> table) {
    os << "Frequency table: " << endl;
    os << "|" << setw(6) << "Score" << "|" << setw(6) << "Count" << "|" << endl;
    os << table;
}

void printStatisticalMeasures(ostream &os, Statistics results) {
    double variance = results.variance();

    os << "Mean: " << results.mean() << endl;
    os << "Variance: " << variance << endl;
    os << "Std: " << sqrt(variance) << endl;
    os << "Max score: " << results.max() << endl;
    os << "Min score: " << results.min() << endl;
    os << "Mode: " << results.mode() << endl;
}

void printMatrix(ostream &os, map<int, map<int, int>> matrix) {
    // find values in the header
    set<int> keys;
    for (auto rowPair: matrix) {
        for (auto colPair: rowPair.second) {
            keys.insert(colPair.first);
        }
    }
    // print header
    os << "|" << setw(5) << " " << "|";
    for (auto key: keys) {
        os << setw(5) << key << "|";
    }
    os << endl;

    for (auto pair: matrix) {
        // one row
        os << "|" << setw(5) << pair.first << "|";
        for (auto key: keys) {
            os << setw(5) << pair.second[key] << "|";
        }
        os << endl;
    }
}

void printProbMatrix(ostream &os, map<int, map<int, float>> matrix) {
    // header
    os << "|" << setw(8) << " " << "|";
    for (auto pair: matrix[0])
            os << setw(8) << pair.first << "|";
    os << endl;

    // content
    for (auto pair: matrix) {
        // one row
        os << "|" << setw(8) << pair.first << "|";
        for (auto l1s: pair.second) {
            os << setw(8) << setprecision(6) << l1s.second << "|";
        }
        os << endl;
    }
}

#endif //EXPERIMENTS_PRINTUTILS_H
