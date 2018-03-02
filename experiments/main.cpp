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
#include "utils/FileSystem.h"
#include "utils/PrintUtils.h"

using namespace std;

SimulationSummary simulate(int year, bool singleGenerator, int runs, bool saveFiles, string format) {
    BitFlip flipMode = BitFlip::NO_FLIP;
    vector<VariateMethod> variates(VECTOR_SIZE, VariateMethod::IID);
    SimulatorSetup* setup = new SimulatorSetup(variates, year, format, flipMode, GenerationDirection::BACKWARD);

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

    map<int, int> table = results.frequencyTable();
    // printFrequencyTable(cout, table);

    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    string resultsPath, setupPath;
    if (saveFiles) {
        resultsPath = Serializer::serialize(results, format, year);
        cout << "Results saved in " << resultsPath << endl;
        setupPath = Serializer::serialize(simulator, format, year);
        cout << "Setup saved in " << setupPath << endl;
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

    return {
            results.max(),
            year,
            resultsPath,
            setupPath
    };
}

int main(int argc, char *argv[]) {
    string dependencyFile;
    string outputFile;
    string summaryFilePath = RESULTS_PATH + "/summary.csv";
    ofstream::openmode summaryFileFlags = ofstream::out;
    for (int i = 1; i < argc; i++) {
        if (strcmp("--dependecy_file", argv[i]) == 0)
            dependencyFile = argv[i + 1];
        else if (strcmp("--output_file", argv[i]) == 0)
            outputFile = argv[i + 1];
        else if (strcmp("--summary_file", argv[i]) == 0)
            summaryFilePath = RESULTS_PATH + "/" + argv[i + 1];
        else if (strcmp("--append", argv[i]) == 0)
            summaryFileFlags |= ofstream::app;
    }

    vector<string> formats = {"TTT"};
    vector<int> years = {2012, 2013, 2014, 2015, 2016, 2017};
    vector<bool> singleGeneratorFlag = {false};
    int runs = (int) 1e2;
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

    ofstream summaryFile(summaryFilePath, summaryFileFlags);
    if (FileSystem::isFileEmpty(summaryFilePath))
        summaryFile << "Format,SingleGenerator,Year,MaxScore,ResultsFile,SetupFile" << endl;

    for (auto year: years) {
        for (auto singleGenerator: singleGeneratorFlag) {
            for (auto format: formats) {
                SimulationSummary summary = simulate(year, singleGenerator, runs, saveFile, format);
                summaryFile << format << "," << singleGenerator << "," << year << ","
                            << summary.maxScore << "," << summary.resultsPath << ","
                            << summary.setupPath << endl;
            }
        }
    }

    return 0;
}