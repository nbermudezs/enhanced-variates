//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Serializer.h"

void Serializer::serialize(Simulator simulator, Statistics statistics) {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    stringstream ss;
    ss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
    string outputFile = ss.str();

    Serializer::serialize(simulator, statistics, outputFile);
}

void Serializer::serialize(Simulator simulator, Statistics statistics, string outputFile) {
    ofstream file(RESULTS_PATH + "/" + outputFile);
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("setup", simulator));
    archive(cereal::make_nvp("statistics", statistics));
}
