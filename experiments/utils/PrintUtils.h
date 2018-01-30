/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/24/18
 */

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

void printBitProbabilities(ostream &os, int runs, Simulator &simulator) {
    if (!simulator.generator.cpt->probabilities.size())
        return;

    os << "Generator statistics" << endl;
    os << "P(bit i = 1) = " << setw(7) << "Obs." << " vs " << setw(8) << "Exp" << endl;
    int minCount = runs, maxCount = 0;
    string as_array = "[";
    for (int i = 0; i < VECTOR_SIZE; i++) {
        if (simulator.generator.bitOnCounts[i] < minCount) {
            minCount = simulator.generator.bitOnCounts[i];
        } else if (simulator.generator.bitOnCounts[i] > maxCount) {
            maxCount = simulator.generator.bitOnCounts[i];
        }
        os << "P(" << setw(5) << "bit" + to_string(VECTOR_SIZE - i - 1) << " = 1) = ";
        os << setw(7) << 1.0 * simulator.generator.bitOnCounts[i] / runs << " vs "
           << setw(8) << simulator.generator.cpt->probabilities[i]
           << endl;

        as_array = as_array + to_string(simulator.generator.bitOnCounts[i]) + ",";
    }
    os << "Min[P(bit = 1)] = " << 1.0 * minCount / runs << endl;
    os << "Max[P(bit = 1)] = " << 1.0 * maxCount / runs << endl;
    os << as_array << "]" << endl;
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

void printMatrix(string filePath, map<int, map<int, int>> matrix) {
    ofstream file;
    file.open(filePath);
    printMatrix(file, matrix);
    file.close();
}

void printProbMatrix(ostream &os, map<int, map<int, double>> matrix) {
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

void printProbMatrix(string filePath, map<int, map<int, double>> matrix) {
    ofstream file;
    file.open(filePath);
    printProbMatrix(file, matrix);
    file.close();
}

#endif //EXPERIMENTS_PRINTUTILS_H
