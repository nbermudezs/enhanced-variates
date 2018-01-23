#include <cmath>
#include <iostream>
#include "output/Serializer.h"

using namespace std;

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

void simulate(int year, bool singleGenerator, int runs, bool saveFile) {
    vector<VariateMethod> variates(VECTOR_SIZE, VariateMethod::IID);
    SimulatorSetup* setup = new SimulatorSetup(variates, year);

    string bracketFilePath = "brackets/TTT/" + to_string(year) + ".txt";
    cout << "Running simulator for " << year << " ..." << endl;
    cout << "Single generator?: " << singleGenerator << endl;
//    cout << "Replications: " << runs << endl;
//    cout << "RAND_MAX: " << RAND_MAX <<  endl;
//    cout << "Bracket path: " << bracketFilePath << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Simulator simulator(setup, runs, bracketFilePath, singleGenerator);
    cout << "Bracket vector: " << simulator.reference << endl;
    Statistics results = simulator.run();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Best bracket:   " << results.bestBracket << endl;

//    cout << "Generator statistics" << endl;
//    int minCount = runs, maxCount = 0;
//    string as_array = "[";
//    for (int i = 0; i < VECTOR_SIZE; i++) {
//        if (simulator.generator.bitOnCounts[i] < minCount) {
//            minCount = simulator.generator.bitOnCounts[i];
//        } else if (simulator.generator.bitOnCounts[i] > maxCount) {
//            maxCount = simulator.generator.bitOnCounts[i];
//        }
//        cout << "P(bit" << (VECTOR_SIZE - i - 1) << " = 1) = " << 1.0 * simulator.generator.bitOnCounts[i] / runs << " vs " << simulator.generator.cpt->probabilities[i] << endl;
//        as_array = as_array + to_string(simulator.generator.bitOnCounts[i]) + ",";
//    }
//    cout << "Min[P(bit = 1)] = " << 1.0 * minCount / runs << endl;
//    cout << "Max[P(bit = 1)] = " << 1.0 * maxCount / runs << endl;
//    cout << as_array << "]" << endl;

    double variance = results.variance();

    cout << "Mean: " << results.mean() << endl;
    cout << "Variance: " << variance << endl;
    cout << "Std: " << sqrt(variance) << endl;
    cout << "Max score: " << results.max() << endl;
    cout << "Min score: " << results.min() << endl;
    cout << "Mode: " << results.mode() << endl;

    cout << "Frequency table: " << endl;
    cout << "|" << setw(6) << "Score" << "|" << setw(6) << "Count" << "|" << endl;
    map<int, int> table = results.frequencyTable();
    cout << table;

//    vector<int> top10 = results.topK(10, true);
//    cout << "Top 10: >" << top10.back() << endl;
//
//    top10 = results.topQuantile(0.1, true);
//    cout << "Top 10%: >" << top10.back() << endl;
    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    if (saveFile) {
        string outputFile = Serializer::serialize(results, year);
        cout << "Results saved in " << outputFile << endl;
        outputFile = Serializer::serialize(simulator, year);
        cout << "Setup saved in " << outputFile << endl;
        cout << "------------------------------------------------------------------" << endl << endl << endl;
    }
}

int main() {
    vector<int> years = {2012, 2013, 2014, 2015, 2016, 2017};
    vector<bool> generator = {true};
    int runs = (int) 1e5;
    bool saveFile = false;

    for (auto year: years) {
        for (auto singleGenerator: generator) {
            simulate(year, singleGenerator, runs, saveFile);
        }
    }

    return 0;
}