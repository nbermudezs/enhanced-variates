//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_CONSTANTS_H
#define EXPERIMENTS_CONSTANTS_H

#include <bitset>
#include <map>
#include <string>
#include <vector>
using namespace std;

const unsigned int VECTOR_SIZE = 63;
const unsigned int REGION_VECTOR_SIZE = 15;
const string BRACKET_METADATA_FOLDER = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/enhanced-variates/experiments/brackets";
const string RESULTS_PATH = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/enhanced-variates/experiments/results";
const string BASE_PATH = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/enhanced-variates/experiments/";
const string TEST_PATH = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/enhanced-variates/experiments/test";
const string SETUP_NAME = "setup";
const string RESULT_NAME = "result";
const string RUN_NAME = "run";

// ENUMS
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

static string ENUM_NAME(SmoothingFunction f) {
    return SmoothingFunctionNames[f];
}

static string ENUM_NAME(VariateMethod f) {
    return VariateMethodNames[f];
}


// TYPEDEFS
typedef bitset<VECTOR_SIZE> BracketData;

//typedef struct BracketData {
//    BracketData() {
//        for (int i = 0; i < VECTOR_SIZE; i++) {
//            x[i] = 0;
//        }
//    }
//
//    explicit BracketData(string data) {
//        for (int i = 0; i < VECTOR_SIZE; i++) {
//            x[VECTOR_SIZE - i - 1] = data[i] - '0';
//        }
//    }
//
//    string to_string() {
//        string result;
//        for (int i = 0; i < VECTOR_SIZE; i++) {
//            float val = x[VECTOR_SIZE - i - 1];
//            if (val == 1) {
//                result.append("1");
//            } else if (val == 0) {
//                result.append("0");
//            } else {
//                result.append("½");
//            }
//        }
//        return result;
//    }
//
//    float x[VECTOR_SIZE];
//    float& operator[](int i) { return x[i]; }
//} BracketData;

// HELPERS
#define ENUM_NAME_HELPER(name) #name

#endif //EXPERIMENTS_CONSTANTS_H
