/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/24/18
 */

#include "Misc.h"

map<int, map<int, int>> Misc::l1Matrix(string filePath) {
    map<int, map<int, int>> result;

    // read JSON file
    ifstream file(filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);

    const CEREAL_RAPIDJSON_NAMESPACE::Value& root = d["brackets"];
    assert(root.IsArray());
    for (unsigned int i = 0; i < root.Size(); i++) {
        const CEREAL_RAPIDJSON_NAMESPACE::Value& rowBracket = root[i]["bracket"];
        int rowYear = stoi(rowBracket["year"].GetString());

        for (unsigned int j = 0; j < root.Size(); j++) {
            const CEREAL_RAPIDJSON_NAMESPACE::Value& colBracket = root[j]["bracket"];
            int colYear = stoi(colBracket["year"].GetString());

            int l1 = Scorer::l1(
                    BracketData(rowBracket["fullvector"].GetString()),
                    BracketData(colBracket["fullvector"].GetString()));
            result[rowYear][colYear] = l1;
        }
    }

    return result;
}

map<int, map<int, double>> Misc::conditionalProbabilityMatrix(string filePath, int year) {
    map<int, map<int, double>> result;
    BracketData refOnes ("111111111111111111111111111111111111111111111111111111111111111");
    BracketData refZeros("000000000000000000000000000000000000000000000000000000000000000");

    BackwardCPT table(filePath, false, year);
    for (unsigned int bit = 0; bit < VECTOR_SIZE; bit++) {
        result[bit][1] = table.P(bit, refOnes);
        result[bit][0] = table.P(bit, refZeros);
    }

    return result;
}
