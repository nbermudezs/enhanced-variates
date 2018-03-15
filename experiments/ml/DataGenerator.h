/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/18/18
 */

#ifndef EXPERIMENTS_DATAGENERATOR_H
#define EXPERIMENTS_DATAGENERATOR_H

#include "../Bracket.h"
#include "../BracketGenerator.h"
#include "../Scorer.h"
#include <fstream>
#include <string>
using namespace std;

class DataGenerator {
public:
    /**
     * Generates a given number of brackets, calculates the scores against the given bracket references
     * and saves the result into a file
     * @param count Number of brackets to be generated
     * @param references Map of reference brackets to calculate scores against
     * @param outputFilePath Path of the file where the brackets will be saved
     */
    static void generate(int count, map<int, Bracket*> references, string outputFilePath);

    /**
     * Generates a given number of brackets and dumps them into a file
     * @param count Number of brackets to be generated
     * @param outputFilePath Path of the file where the brackets will be saved
     */
    static void generateBracketOnly(int count, string outputFilePath);

    /**
     * Generates a given number of brackets and dumps them into a file using the given
     * configuration for the bracket generator
     * @param count Number of brackets to be generated
     * @param outputFilePath Path of the file where the brackets will be saved
     * @param config The configuration for the BracketGenerator
     */
    static void generateBracketOnlyWithConfig(int count, string outputFilePath, GeneratorConfig config);
};


#endif //EXPERIMENTS_DATAGENERATOR_H
