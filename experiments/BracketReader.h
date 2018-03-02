/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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

    /**
     * Reads the given file and creates corresponding bracket objects for each of the
     * brackets found in the file
     * @param filePath  The path of the file to load the brackets from
     * @return A map of Brackets indexed by year
     */
    static map<int, Bracket*> readAll(string filePath);

    /**
     * Reads the given file that contains some score rankings from 2013 to present.
     * It selects only the ranks corresponding to the given year.
     * @param filePath The path of the file to read
     * @param year The particular to get rank for
     * @return A map containing the rank of the score and the actual score.
     */
    static map<int, int> readESPNScores(string filePath, int year);

    /**
     * Reads the given file that contains some score rankings from 2013 to present.
     * @param filePath The path of the file to read
     * @return A map containing the rank of the score and the actual score.
     */
    static map<int, map<int, int>> readESPNScores(string filePath);
};


#endif //EXPERIMENTS_BRACKETREADER_H
