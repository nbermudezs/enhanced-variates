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

SimulationSummary simulate(int year, bool singleGenerator, int runs, bool saveFiles, string format,
                           GroupSelector groupSelector, double retentionP) {
    BitFlip flipMode = BitFlip::NO_FLIP;
    vector<VariateMethod> variates(VECTOR_SIZE, VariateMethod::IID);
    // TODO: change constructor to pass the seed if in --reproduce mode.
    SimulatorSetup* setup = new SimulatorSetup(variates, year, format, flipMode,
                                               GenerationDirection::BACKWARD, groupSelector);
    setup->retentionP = retentionP;

    string bracketFilePath = "brackets/" + format + "/allBrackets" + format + ".json";
    cout << "Running simulator for " << year << " ..." << endl;
    // cout << "Single generator?: " << singleGenerator << endl;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    Simulator simulator(setup, runs, bracketFilePath, singleGenerator);
    cout << "Bracket vector: " << simulator.reference << endl;
    cout << "Group selector: " << groupSelector.to_string() << endl;
    cout << "Group CRN/ARN retention P: " << retentionP << endl;
    Statistics results = simulator.run();
    chrono::steady_clock::time_point stop = chrono::steady_clock::now();
    cout << "Best bracket:   " << results.bestBracket << endl;
    bool madeItToTop100 = results.max() >= simulator.getScoreRanks()[100];
    cout << "In top-100? " << (madeItToTop100 ? "Yes" : "No") << endl;

    // uncomment to print the observed probability of a bit being 1 vs the expected one (from history)
    // printBitProbabilities(cout, runs, simulator);

    printStatisticalMeasures(cout, results);

    map<int, int> table = results.frequencyTable();
    // printFrequencyTable(cout, table);

    cout << "Took " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << endl;

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
            setupPath,
            madeItToTop100,
            setup->masterSeed
    };
}

int main(int argc, char *argv[]) {
    string dependencyFile;
    string outputFile;
    string summaryFilePath = RESULTS_PATH + "/summary.csv";
    string setupFilePath;
    ofstream::openmode summaryFileFlags = ofstream::out;
    for (int i = 1; i < argc; i++) {
        if (strcmp("--dependency_file", argv[i]) == 0)
            dependencyFile = argv[i + 1];
        else if (strcmp("--output_file", argv[i]) == 0)
            outputFile = argv[i + 1];
        else if (strcmp("--summary_file", argv[i]) == 0)
            summaryFilePath = RESULTS_PATH + "/" + argv[i + 1];
        else if (strcmp("--append", argv[i]) == 0)
            summaryFileFlags |= ofstream::app;
        else if (strcmp("--reproduce", argv[i]) == 0)
            setupFilePath = argv[i + 1];
    }
    // TODO: read setupFilePath and re-run the experiment with the given setup

    vector<string> formats = {"TTT"};
    vector<int> years = {2013, 2014, 2015, 2016, 2017};
    vector<bool> singleGeneratorFlag = {false};
    int runs = (int) 1e4;
    bool saveFile = false;

#ifdef CREATE_L1_MATRICES
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
#endif

    ofstream summaryFile(summaryFilePath, summaryFileFlags);
    if (FileSystem::isFileEmpty(summaryFilePath))
        summaryFile << "Format,Groups,ReP,SingleGenerator,Year,MaxScore,Top100,ResultsFile,SetupFile,MasterSeed" << endl;

    for (int p = 10; p >= 0; p--)
        for (int i = 0; i < 128; i++) {
            GroupSelector groupSelector(i);
            for (auto year: years) {
                for (auto singleGenerator: singleGeneratorFlag) {
                    for (auto format: formats) {
                        SimulationSummary summary = simulate(year, singleGenerator, runs, saveFile, format, groupSelector, p / 10.);
                        summaryFile << format << ","
                                    << groupSelector.to_string() << ","
                                    << p / 10. << "," // same value in BracketGenerator::get
                                    << singleGenerator << ","
                                    << year << ","
                                    << summary.maxScore << ","
                                    << summary.madeItToTop100 << ","
                                    << summary.resultsPath << ","
                                    << summary.setupPath << ","
                                    << summary.masterSeed << endl;
                    }
                }
            }
        }


    return 0;
}