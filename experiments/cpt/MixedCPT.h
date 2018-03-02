/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/28/18
 */

#ifndef EXPERIMENTS_MIXEDCPT_H
#define EXPERIMENTS_MIXEDCPT_H

#include <cmath>
#include <map>
#include <string>
#include <vector>
#include "BaseCPT.h"
#include "../Constants.h"

class MixedCPT: public BaseCPT {
public:
    /**
     * Overrides
     */

    /**
     * Returns the unconditional probability of the @param{bitId} being 1
     * @param bitId index of the bit. @see Constants::VECTOR_SIZE
     * @return the probability of the @param{bitId} = 1.
     */
    double P(int bitId);

    /**
     * Returns the conditional probability of the @param{bitId} being 1
     * @param bitId index of the bit. @see Constants::VECTOR_SIZE
     * @param bracket bracket generated so far, the conditional information
     * to find P(bit = 1) will be taken from this.
     * @return the conditional probability of the given bit being 1.
     */
    double P(int bitId, BracketData data);

    static MixedCPT& getInstance(string, bool, int);
    static MixedCPT& getInstance(string filePath, bool isMetadataFile, int year,
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
    static MixedCPT& getInstance(string filePath, bool isMetadataFile, int year,
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
    MixedCPT() = default;

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
    MixedCPT(string filePath, bool isMetadataFile, int year);

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
    MixedCPT(string filePath, bool isMetadataFile, int year, map<int, double> overrides);

    /**
     * Specifies at which bit the generation process should start
     * @return the start bit (0)
     */
    int startBit() { return VECTOR_SIZE - 1; }

    /**
     * Specifies at which bit the generation process should stop
     * @return the end bit (Constants::VECTOR_SIZE - 1)
     */
    int endBit() { return 0; }

    /**
     * Determines whether the traversing of the vector happens from left to right or vice-versa.
     * @return delta (1)
     */
    int bitAdvance() { return -1; }

private:
    static map<string, MixedCPT*> instances;
    int getParentBit(int bit);
};


#endif //EXPERIMENTS_MIXEDCPT_H
