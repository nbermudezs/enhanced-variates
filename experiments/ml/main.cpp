/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/18/18
 */

#include "../BracketReader.h"
#include "../utils/PrintUtils.h"
#include "DataGenerator.h"
using namespace std;

int main() {
    /* This code was used to generate some files for clustering analysis */
    auto references = BracketReader::readAll("brackets/TTT/allBracketsTTT.json");
    DataGenerator::generate(1000000, references, "ml/data/train.csv");
    DataGenerator::generate(2000000, references, "ml/data/test.csv");

    /* The code below was used to generate the brackets to check against 2018. */
    DataGenerator::generateBracketOnly(10000, "ml/data/10kBackwardPModel.csv");
    DataGenerator::generateBracketOnly(100000, "ml/data/100kBackwardPModel.csv");
    DataGenerator::generateBracketOnly(1000000, "ml/data/1milBackwardPModel.csv");
    DataGenerator::generateBracketOnly(10000000, "ml/data/10milBackwardPModel.csv");

    auto config = GeneratorConfig(GroupSelector("1100111"), 0.8);
    DataGenerator::generateBracketOnlyWithConfig(10000, "ml/data/10kERNModel-1100111.csv", config);
    DataGenerator::generateBracketOnlyWithConfig(100000, "ml/data/100kERNModel-1100111.csv", config);
    DataGenerator::generateBracketOnlyWithConfig(1000000, "ml/data/1milERNModel-1100111.csv", config);
    DataGenerator::generateBracketOnlyWithConfig(10000000, "ml/data/10milERNModel-1100111.csv", config);

    config = GeneratorConfig(GroupSelector("0101100"), 0.8);
    DataGenerator::generateBracketOnlyWithConfig(10000, "ml/data/10kERNModel-0101100.csv", config);
    DataGenerator::generateBracketOnlyWithConfig(100000, "ml/data/100kERNModel-0101100.csv", config);
    DataGenerator::generateBracketOnlyWithConfig(1000000, "ml/data/1milERNModel-0101100.csv", config);
    DataGenerator::generateBracketOnlyWithConfig(10000000, "ml/data/10milERNModel-0101100.csv", config);


    return 0;
}