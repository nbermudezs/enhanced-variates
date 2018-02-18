/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#include <cmath>
#include <iostream>
#include "analysis/Misc.h"
#include "output/Serializer.h"
#include "utils/PrintUtils.h"

using namespace std;

void simulate(int year, bool singleGenerator, int runs, bool saveFiles, string format) {
    vector<VariateMethod> variates(VECTOR_SIZE, VariateMethod::IID);
    SimulatorSetup* setup = new SimulatorSetup(variates, year, format, false, GenerationDirection::BACKWARD);

    string bracketFilePath = "brackets/" + format + "/allBrackets" + format + ".json";
    cout << "Running simulator for " << year << " ..." << endl;
    cout << "Single generator?: " << singleGenerator << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Simulator simulator(setup, runs, bracketFilePath, singleGenerator);
    cout << "Bracket vector: " << simulator.reference << endl;
    Statistics results = simulator.run();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Best bracket:   " << results.bestBracket << endl;

    // uncomment to print the observed probability of a bit being 1 vs the expected one (from history)
    // printBitProbabilities(cout, runs, simulator);

    printStatisticalMeasures(cout, results);

    // map<int, int> table = results.frequencyTable();
    // printFrequencyTable(cout, table);

    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    if (saveFiles) {
        string outputFile = Serializer::serialize(results, format, year);
        cout << "Results saved in " << outputFile << endl;
        outputFile = Serializer::serialize(simulator, format, year);
        cout << "Setup saved in " << outputFile << endl;
        cout << "------------------------------------------------------------------" << endl << endl << endl;
/*
        for (auto roundPair: RoundNames) {
            string tmp = outputFile;
            tmp.replace(tmp.end() - 10, tmp.end(), "L1Matrix-" + roundPair.second + ".txt");
            auto matrix = results.l1DistributionMatrix(roundPair.first);
            string filePath = RESULTS_PATH;
            filePath.append("/" + tmp);
            printMatrix(filePath, matrix);
        }
*/
    }

    cout << "=======================================================================" << endl;
}

int main() {
    vector<string> formats = {"TTT", "FFF"};
    vector<int> years = {2012, 2013, 2014, 2015, 2016, 2017};
    vector<bool> singleGeneratorFlag = {true};
    int runs = (int) 1e4;
    bool saveFile = false;

    for (auto format: formats) {
        // uncomment to print out L1 distance between the 33 years of brackets.
        auto l1Matrix = Misc::l1Matrix(BASE_PATH + "/brackets/" + format + "/allBrackets" + format + ".json");
        printMatrix(RESULTS_PATH + "/" + format + "/L1Matrices/all" + format + ".txt", l1Matrix);

        // uncomment to print out conditional probability matrix
        for (auto excludedYear: {0, 2012, 2013, 2014, 2015, 2016, 2017}) {
            auto conditionalProbMatrix = Misc::conditionalProbabilityMatrix(
                    BASE_PATH + "/brackets/" + format + "/allBrackets" + format + ".json",
                    excludedYear);
            printProbMatrix(
                    RESULTS_PATH + "/" + format + "/CPT/all" + format + "-" + to_string(excludedYear) + ".txt",
                    conditionalProbMatrix);
        }
    }

    for (auto year: years) {
        for (auto singleGenerator: singleGeneratorFlag) {
            for (auto format: formats) {
                simulate(year, singleGenerator, runs, saveFile, format);
            }
        }
    }

    return 0;
}