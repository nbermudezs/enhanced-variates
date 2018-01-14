//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_CONSTANTS_H
#define EXPERIMENTS_CONSTANTS_H

#include<string>
using namespace std;

const unsigned int VECTOR_SIZE = 63;
const string BRACKET_METADATA_FOLDER = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/DataForNestor";
const string RESULTS_PATH = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/enhanced-variates/experiments/results";
const string BASE_PATH = "/Users/nbermudezs/Documents/Personal/College/UIUC/Research.nosync/shj/enhanced-variates/experiments/";
const string SETUP_NAME = "setup";
const string RESULT_NAME = "result";
const string RUN_NAME = "run";

enum class VariateMethod { IID, COMMON, ANTITHETIC };

#endif //EXPERIMENTS_CONSTANTS_H
