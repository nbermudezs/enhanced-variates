/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#include "Serializer.h"

string Serializer::getName() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    stringstream ss;
    ss << put_time(&tm, "%d%m%Y%H%M%S");
    return ss.str();
}

string Serializer::serialize(Simulator simulator, string format, int year) {
    string outputFile = format + "/" + to_string(year) + "/" + to_string(year) + "_" +
            Serializer::getName() + SETUP_NAME + ".json";
    Serializer::serialize(simulator, format, outputFile);
    return outputFile;
}

string Serializer::serialize(Statistics statistics, string format, int year) {
    string outputFile = format + "/" + to_string(year) + "/" + to_string(year) + "_" +
            Serializer::getName() + RESULT_NAME + ".json";
    Serializer::serialize(statistics, format, outputFile);
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
    archive(cereal::make_nvp("VERSION", VERSION));
    archive(cereal::make_nvp("setup", simulator));
    archive(cereal::make_nvp("statistics", statistics));
}

void Serializer::serialize(Simulator simulator, string format, string outputFile) {
    ofstream file(RESULTS_PATH + "/" + outputFile);
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("VERSION", VERSION));
    archive(cereal::make_nvp("format", format));
    archive(cereal::make_nvp("setup", simulator));
}

void Serializer::serialize(Statistics statistics, string format, string outputFile) {
    ofstream file(RESULTS_PATH + "/" + outputFile);
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("VERSION", VERSION));
    archive(cereal::make_nvp("format", format));
    archive(cereal::make_nvp("statistics", statistics));
}
