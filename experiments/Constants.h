/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#ifndef EXPERIMENTS_CONSTANTS_H
#define EXPERIMENTS_CONSTANTS_H

#include <bitset>
#include <map>
#include <string>
#include <vector>
using namespace std;

const unsigned int VECTOR_SIZE = 63;
const unsigned int REGION_VECTOR_SIZE = 15;
const unsigned int N_REGIONS = 4;
const string BRACKET_METADATA_FOLDER = "../brackets";
const string RESULTS_PATH = "../results";
const string BASE_PATH = "../";
const string TEST_PATH = "../test";
const string SETUP_NAME = "setup";
const string RESULT_NAME = "result";
const string RUN_NAME = "run";
const string VERSION = "1.2";
const float LAPLACE_SMOOTHING = 0.01;


// ENUMS
enum class GenerationDirection {
    BACKWARD = 0,
    FORWARD,
    BASELINE_4 // round of 64 using unconditional probabilities, others using backwards
};
static map<GenerationDirection, string> GenerationDirectionNames = {
        pair<GenerationDirection, string>(GenerationDirection::BACKWARD, "BACKWARD"),
        pair<GenerationDirection, string>(GenerationDirection::FORWARD, "FORWARD"),
        pair<GenerationDirection, string>(GenerationDirection::BASELINE_4, "BASELINE_4"),
};

/**
 * This enumeration determines how to decide whether a year should be excluded
 * when calculating the conditional probability tables.
 * NONE means that all years should be included.
 * EXACT means that if a year matches the reference year its data must not be used.
 * AFTER means that ALL years AFTER the given year must not be used.
 */
enum class CptYearExclusion {
    NONE = 0,
    EXACT,
    AFTER
};

/**
 * Enumeration to keep track of the supported models.
 * @TODO: a flag in main.cpp should control which one should be used.
 */
enum class ModelType {
    SINGLE_BIT = 0,
    TRIPLETS
};
static map<ModelType, string> ModelTypeNames = {
        pair<ModelType, string>(ModelType::SINGLE_BIT, "SINGLE_BIT"),
        pair<ModelType, string>(ModelType::TRIPLETS, "TRIPLETS")
};

enum class ROUND {
    ROUND_64 = 0,
    ROUND_32,
    ROUND_16,
    REGION_FINALS,
    SEMI_FINALS,
    FINAL,
    ALL
};
static map<ROUND, string> RoundNames = {
        pair<ROUND, string>(ROUND::ROUND_64, "64"),
        pair<ROUND, string>(ROUND::ROUND_32, "32"),
        pair<ROUND, string>(ROUND::ROUND_16, "16"),
        pair<ROUND, string>(ROUND::REGION_FINALS, "RF"),
        pair<ROUND, string>(ROUND::SEMI_FINALS, "SF"),
        pair<ROUND, string>(ROUND::FINAL, "F"),
        pair<ROUND, string>(ROUND::ALL, "ALL")
};

enum class VariateMethod { IID = 0, COMMON, ANTITHETIC };
static map<VariateMethod, string> VariateMethodNames = {
        pair<VariateMethod, string>(VariateMethod::IID, "IID"),
        pair<VariateMethod, string>(VariateMethod::COMMON, "COMMON"),
        pair<VariateMethod, string>(VariateMethod::ANTITHETIC, "ANTITHETIC")
};

enum class SmoothingFunction { AND = 0, OR, XOR, AVG };
static map<SmoothingFunction, string> SmoothingFunctionNames = {
        pair<SmoothingFunction, string>(SmoothingFunction::AND, "AND"),
        pair<SmoothingFunction, string>(SmoothingFunction::OR, "OR"),
        pair<SmoothingFunction, string>(SmoothingFunction::XOR, "XOR"),
        pair<SmoothingFunction, string>(SmoothingFunction::AVG, "AVG")
};

enum class BitFlip { NO_FLIP = 0, SINGLE, TWO_BITS };
static map<BitFlip, string> BitFlipNames = {
        pair<BitFlip, string>(BitFlip::NO_FLIP, "NO_FLIP"),
        pair<BitFlip, string>(BitFlip::SINGLE, "SINGLE"),
        pair<BitFlip, string>(BitFlip::TWO_BITS, "TWO_BITS")
};

static string ENUM_NAME(SmoothingFunction f) {
    return SmoothingFunctionNames[f];
}

static string ENUM_NAME(VariateMethod f) {
    return VariateMethodNames[f];
}


// TYPEDEFS
typedef bitset<VECTOR_SIZE> BracketData;

struct SimulationSummary {
    int maxScore;
    int year;
    string resultsPath;
    string setupPath;
    long madeItToTop100;
    unsigned int masterSeed;
    map<pair<int, int>, int> binnedScores;
};

// HELPERS
#define ENUM_NAME_HELPER(name) #name

#endif //EXPERIMENTS_CONSTANTS_H
