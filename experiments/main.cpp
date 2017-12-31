#include <cmath>
#include <iostream>
#include "output/Serializer.h"
#include "Simulator.h"

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

int main() {
    cout << "Running simulator..." << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Simulator simulator(1e7);
    Statistics results = simulator.run("reference_bracket_path");
    chrono::steady_clock::time_point end= chrono::steady_clock::now();

    float variance = results.variance();

    cout << "Mean: " << results.mean() << endl;
    cout << "Variance: " << variance << endl;
    cout << "Std: " << sqrt(variance) << endl;
    cout << "Max score: " << results.max() << endl;
    cout << "Min score: " << results.min() << endl;

    cout << "Frequency table: " << endl;
    cout << "|" << setw(6) << "Score" << "|" << setw(6) << "Count" << "|" << endl;
    map<int, int> table = results.frequencyTable();
    cout << table;

    vector<int> top10 = results.topK(10, true);
    cout << "Top 10: " << top10 << endl;
    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    string outputFile = Serializer::serialize(results);
    cout << "Results saved in " << outputFile << endl;
    outputFile = Serializer::serialize(simulator);
    cout << "Setup saved in " << outputFile << endl;

    return 0;
}