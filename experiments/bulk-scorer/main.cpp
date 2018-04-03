/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 4/3/18
 */

#include <fstream>
#include "../BracketReader.h"
#include "../utils/PrintUtils.h"
#include "../Scorer.h"
using namespace std;

/* bulk-scorer/main.cpp source_filepath dest_filepath model-name runs threshold_score */
int main(int argc, char* argv[]) {
    // TODO: change this to use any reference year instead of the hardcoded vector
    auto ref = new Bracket(BracketData("001001110111110101111110001110101011011100111111101111110101010"));

    auto source = argv[1];
    auto dest = argv[2];
    auto name = argv[3];
    auto runs = stoi(argv[4]);
    auto threshold = argc < 6 ? 0 : stoi(argv[5]);

    ifstream sourceFile(source);
    assert(sourceFile.is_open());

    ofstream out;
    out.open(dest);

    cout << "Processing " << source << endl;
    string line;
    out << "Vector, Score, R64, R32, S16, E8, F4, NCG" << endl;
    int count = 0;
    while (getline(sourceFile, line)) {
        cout << "Line #" << count++ << "\r";
        line.erase(line.length() - 1);
        auto input = new Bracket(BracketData(line));
        auto score = Scorer::byRound(ref, input);
        if (threshold > 0 && score[6] < threshold)
            continue;
        out << line << "," << score[6] << ","
            // R64              R32                 S16                 E8                  F4                  NCG
            << score[0] << "," << score[1] << "," << score[2] << "," << score[3] << "," << score[4] << "," << score[5] << endl;
    }

    sourceFile.close();
    return 0;
}

