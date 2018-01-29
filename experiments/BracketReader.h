//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#ifndef EXPERIMENTS_BRACKETREADER_H
#define EXPERIMENTS_BRACKETREADER_H


#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/istreamwrapper.h>
#include <fstream>
#include <string>
#include "Bracket.h"
using namespace std;


class BracketReader {
public:

    /**
        Returns the bracket from the given file.
        The file should be a text file only containing the 0/1 vector representation of the bracket

        @param filePath The path of the file to load the bracket from
        @return The Bracket object
    */
    static Bracket* readSingle(string filePath);

    /**
        Returns the bracket from the given file.
        The file should be a JSON file that contains a list of brackets. Each bracket sub-document
        should have a year and a fullvector keys.

        @param filePath The path of the file to load the brackets from
        @param year The specific year to be selected from the list of brackets
        @return The Bracket object
    */
    static Bracket* readSingle(string filePath, int year);
};


#endif //EXPERIMENTS_BRACKETREADER_H
