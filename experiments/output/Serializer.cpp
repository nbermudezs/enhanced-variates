//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Serializer.h"

string Serializer::getName() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    stringstream ss;
    ss << put_time(&tm, "%d%m%Y%H%M%S");
    return ss.str();
}

string Serializer::serialize(Simulator simulator, int year) {
    string outputFile = to_string(year) + "/" + to_string(year) + "_" + Serializer::getName() + SETUP_NAME + ".json";
    Serializer::serialize(simulator, outputFile);
    return outputFile;
}

string Serializer::serialize(Statistics statistics, int year) {
    string outputFile = to_string(year) + "/" + to_string(year) + "_" + Serializer::getName() + RESULT_NAME + ".json";
    Serializer::serialize(statistics, outputFile);
    return outputFile;
}

string Serializer::serialize(Simulator simulator, Statistics statistics) {
    string outputFile = RUN_NAME + Serializer::getName();
    Serializer::serialize(simulator, statistics, outputFile);
    return outputFile;
}

void Serializer::serialize(Simulator simulator, Statistics statistics, string outputFile) {
    ofstream file(RESULTS_PATH + "/" + outputFile);
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("setup", simulator));
    archive(cereal::make_nvp("statistics", statistics));
}

void Serializer::serialize(Simulator simulator, string outputFile) {
    ofstream file(RESULTS_PATH + "/" + outputFile);
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("setup", simulator));
}

void Serializer::serialize(Statistics statistics, string outputFile) {
    ofstream file(RESULTS_PATH + "/" + outputFile);
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("statistics", statistics));
}
