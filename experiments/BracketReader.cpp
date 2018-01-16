//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "BracketReader.h"


Bracket* BracketReader::read(string filePath) {
    ifstream inFile(BASE_PATH + filePath);
    string vectorData;
    getline(inFile, vectorData);
    BracketData data(vectorData);
    inFile.close();
    return new Bracket(data);
}