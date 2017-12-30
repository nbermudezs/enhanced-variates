#include <iostream>
#include "BracketGenerator.h"
#include "BracketReader.h"
#include "Scorer.h"
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
    BracketGenerator generator;

    Bracket* reference = BracketReader::read("reference_bracket_path");
    Bracket* input = generator.get();
    int score = Scorer::eval(reference, input);
    cout << "Reference: " << reference->data;
    cout << "Generated: " << input->data;
    cout << "Score: " << score << endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Simulator simulator;
    simulator.run("reference_bracket_path");
    chrono::steady_clock::time_point end= chrono::steady_clock::now();
    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms";

    return 0;
}