/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/18/18
 */

#include "DataGenerator.h"

void DataGenerator::generate(int count, map<int, Bracket *> references, string outputFilePath) {
    ofstream out(BASE_PATH + "/" + outputFilePath);

    for (auto pair: references)
        out << pair.first << ",";
    out << endl;

    auto generator = new BracketGenerator(GenerationDirection::BACKWARD, "TTT", 0);
    for (int i = 0; i < count; i++) {
        Bracket* bracket = generator->get();
        out << bracket->data.to_string();
        for (auto pair: references) {
            int ESPNScore = Scorer::evalWithRegionGrouping(pair.second, bracket);
            out << "," << ESPNScore;
        }
        out << endl;
    }
}

void DataGenerator::generateBracketOnly(int count, string outputFilePath) {
    ofstream out(BASE_PATH + "/" + outputFilePath);

    auto generator = new BracketGenerator(GenerationDirection::BACKWARD, "TTT", 0);
    for (int i = 0; i < count; i++) {
        Bracket* bracket = generator->get();
        out << bracket->data.to_string() << endl;
    }
}

void DataGenerator::generateBracketOnlyWithConfig(int count, string outputFilePath, GeneratorConfig config) {
    ofstream out(BASE_PATH + "/" + outputFilePath);

    auto generator = new BracketGenerator(GenerationDirection::BACKWARD, "TTT", 0);
    for (int i = 0; i < count; i++) {
        Bracket* bracket = generator->get(config);
        out << bracket->data.to_string() << endl;
    }
}

