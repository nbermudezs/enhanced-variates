/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#ifndef EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
#define EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H

#include <cmath>
#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/istreamwrapper.h>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "BaseCPT.h"
#include "../Constants.h"
using namespace std;

const int YEARS = 33;


class ConditionalProbabilityTable: public BaseCPT {
public:
    /**
     * Overrides
     */

    double P(int bitId);
    double P(int bitId, BracketData data);

    static ConditionalProbabilityTable& getInstance(string, bool, int);
    static ConditionalProbabilityTable& getInstance(string filePath, bool isMetadataFile, int year,
                                                    map<int, double> overrides);

    /**
     * Returns an instance of this class based on the provided attributes.
     * This implements the singleton pattern design so the same instance is returned
     * given the @param{instanceKey}
     * @param filePath file containing the brackets or metadata
     * @param isMetadataFile whether the provided @param{filePath} corresponds to
     * a metadata file or not. If false, the file should be a JSON file.
     * @param year year to be omitted. Only in effect if @param{isMetadataFile} is false.
     * @param overrides a map where the keys are bit ids and the values are the expected probability
     * of such bit being 1. These probabilities override whatever probability computed from
     * the provided file.
     * @param instanceKey key associated with this set of parameters. Given a key the
     * same instance will be returned every time this method is called.
     * @return an instance of this class.
     */
    static ConditionalProbabilityTable& getInstance(string filePath, bool isMetadataFile, int year,
                                                    map<int, double> overrides, string instanceKey);

    /**
     * Attributes
     */
    int historyCount = 0;
    map<int, map<int, int>> conditionalCounts; // { "bit0": { "parent-0": a, "parent-1": b }, ... }
    map<int, int> totalCounts;

    /**
     * Constructs an empty instance of this class.
     */
    ConditionalProbabilityTable();

    /**
     * Creates an instance of this class
     * @param filePath path of the file containing the brackets' info
     * @param isMetadataFile boolean flag that indicates whether the provided file
     * already has the summarized counts and there is no need to process the
     * individual brackets. If this flag is false the file is expected to contain all
     * the brackets that should be analyzed.
     * @param year indicates which year, if any, must be omitted from the brackets
     * contained in the file. This argument only has effect when isMetadataFile is false.
     */
    ConditionalProbabilityTable(string filePath, bool isMetadataFile, int year);

    /**
     * Creates an instance of this class
     * @param filePath path of the file containing the brackets' info
     * @param isMetadataFile boolean flag that indicates whether the provided file
     * already has the summarized counts and there is no need to process the
     * individual brackets. If this flag is false the file is expected to contain all
     * the brackets that should be analyzed.
     * @param year indicates which year, if any, must be omitted from the brackets
     * contained in the file. This argument only has effect when isMetadataFile is false.
     * @param overrides a map where the keys are bit ids and the values are the expected probability
     * of such bit being 1. These probabilities override whatever probability computed from
     * the provided file.
     */
    ConditionalProbabilityTable(string filePath, bool isMetadataFile, int year, map<int, double> overrides);

private:
    static map<string, ConditionalProbabilityTable*> instances;
};


#endif //EXPERIMENTS_CONDITIONALPROBABILITYTABLE_H
