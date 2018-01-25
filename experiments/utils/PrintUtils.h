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

void printL1Matrix(ostream &os, map<int, map<int, int>> matrix) {
    // header
    os << "|" << setw(5) << " " << "|";
    for (auto pair: matrix)
        os << setw(5) << pair.first << "|";
    os << endl;

    // content
    for (auto pair: matrix) {
        // one row
        os << "|" << setw(5) << pair.first << "|";
        for (auto l1s: pair.second) {
            os << setw(5) << l1s.second << "|";
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
