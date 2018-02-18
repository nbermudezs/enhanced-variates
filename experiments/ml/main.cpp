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
    auto references = BracketReader::readAll("brackets/TTT/allBracketsTTT.json");
    DataGenerator::generate(1000000, references, "ml/data/train.csv");
    DataGenerator::generate(2000000, references, "ml/data/test.csv");
    return 0;
}