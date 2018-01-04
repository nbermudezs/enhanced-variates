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

ostream &operator<<(ostream &os, Bracket* bracket) {
    os << bracket->data;
    return os;
}

int main() {
    vector<VariateMethod> variates(VECTOR_SIZE, VariateMethod::IID);
    SimulatorSetup* setup = new SimulatorSetup(variates);
    int runs = (int) 1e6;

    string bracketFilePath = "brackets/2017.txt";
    cout << "Running simulator..." << endl;
    cout << "Replications: " << runs << endl;
    cout << "Bracket path: " << bracketFilePath << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Simulator simulator(setup, runs, bracketFilePath);
    cout << "Bracket vector: " << simulator.reference << endl;
    Statistics results = simulator.run();
    chrono::steady_clock::time_point end= chrono::steady_clock::now();

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

    vector<int> top10 = results.topK(10, true);
    cout << "Top 10: >" << top10.back() << endl;

    top10 = results.topQuantile(0.1, true);
    cout << "Top 10%: >" << top10.back() << endl;
    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    string outputFile = Serializer::serialize(results);
    cout << "Results saved in " << outputFile << endl;
    outputFile = Serializer::serialize(simulator);
    cout << "Setup saved in " << outputFile << endl;

    return 0;
}