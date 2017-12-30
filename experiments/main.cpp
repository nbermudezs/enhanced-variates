#include <iostream>
#include "Scorer.h"

using namespace std;

int main() {
    Scorer *scorer = new Scorer();

    vector<int> reference = {1,0,0,0};
    vector<int> input = {0,0,0,0};
    int score = scorer->eval(reference, input);
    cout << "Score: " << score << endl;
    return 0;
}