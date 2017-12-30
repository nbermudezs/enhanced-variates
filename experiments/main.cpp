#include <iostream>
#include "Simulator.h"

using namespace std;

ostream &operator<<(ostream &os, vector<int> &v)
{
    for(auto &i: v) {
        os << i;
    }
    os << endl;
    return os;
}

int main() {
    cout << "Running simulator..." << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Simulator simulator;
    Statistics results = simulator.run("reference_bracket_path");
    chrono::steady_clock::time_point end= chrono::steady_clock::now();
    cout << "Mean: " << results.mean() << endl;
    cout << "Max score: " << results.max() << endl;
    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms";

    return 0;
}