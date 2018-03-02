/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#include "BracketReader.h"


Bracket* BracketReader::readSingle(string filePath) {
    ifstream inFile(BASE_PATH + filePath);
    string vectorData;
    getline(inFile, vectorData);
    BracketData data(vectorData);
    inFile.close();
    return new Bracket(data);
}

Bracket *BracketReader::readSingle(string filePath, int year) {
    ifstream file(BASE_PATH + filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);

    const CEREAL_RAPIDJSON_NAMESPACE::Value& root = d["brackets"];
    assert(root.IsArray());

    for (unsigned int i = 0; i < root.Size(); i++) {
        const CEREAL_RAPIDJSON_NAMESPACE::Value& bracket = root[i]["bracket"];
        int bracketYear = stoi(bracket["year"].GetString());
        if (bracketYear == year)
            return new Bracket(BracketData(bracket["fullvector"].GetString()));
    }

    return nullptr;
}

map<int, Bracket *> BracketReader::readAll(string filePath) {
    map<int, Bracket *> result;

    ifstream file(BASE_PATH + filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);

    const CEREAL_RAPIDJSON_NAMESPACE::Value& root = d["brackets"];
    assert(root.IsArray());

    for (unsigned int i = 0; i < root.Size(); i++) {
        const CEREAL_RAPIDJSON_NAMESPACE::Value& bracket = root[i]["bracket"];
        int bracketYear = stoi(bracket["year"].GetString());
        Bracket* instance = new Bracket(BracketData(bracket["fullvector"].GetString()));
        result[bracketYear] = instance;
    }

    return result;
}

map<int, int> BracketReader::readESPNScores(string filePath, int year) {
    map<int, int> result;

    ifstream file(BASE_PATH + filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);

    const CEREAL_RAPIDJSON_NAMESPACE::Value& root = d["scores"];
    assert(root.IsArray());

    for (unsigned int i = 0; i < root.Size(); i++) {
        auto& yearData = root[i];
        int itemYear = yearData["year"].GetInt();
        if (itemYear != year)
            continue;
        auto& ranks = yearData["rank"];
        for (auto itr = ranks.MemberBegin(); itr != ranks.MemberEnd(); ++itr) {
            result[stoi(itr->name.GetString())] = itr->value.GetInt();
        }
    }

    return result;
}

map<int, map<int, int>> BracketReader::readESPNScores(string filePath) {
    map<int, map<int, int>> result;

    ifstream file(BASE_PATH + filePath);
    CEREAL_RAPIDJSON_NAMESPACE::IStreamWrapper isw(file);
    CEREAL_RAPIDJSON_NAMESPACE::Document d;
    d.ParseStream(isw);

    const CEREAL_RAPIDJSON_NAMESPACE::Value& root = d["scores"];
    assert(root.IsArray());

    for (unsigned int i = 0; i < root.Size(); i++) {
        auto& yearData = root[i];
        int itemYear = yearData["year"].GetInt();
        auto& ranks = yearData["rank"];
        for (auto itr = ranks.MemberBegin(); itr != ranks.MemberEnd(); ++itr) {
            result[itemYear][stoi(itr->name.GetString())] = itr->value.GetInt();
        }
    }

    return result;
}
