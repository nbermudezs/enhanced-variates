#include <iostream>
#include "BracketGenerator.h"
#include "BracketReader.h"
#include "Scorer.h"

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

    Bracket* reference = BracketReader::read("some_path");
    Bracket* input = generator.get();
    int score = Scorer::eval(reference, input);
    cout << "Reference: " << reference->data;
    cout << "Generated: " << input->data;
    cout << "Score: " << score << endl;
    return 0;
}