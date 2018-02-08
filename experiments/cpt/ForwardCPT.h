/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/7/18
 */

#ifndef EXPERIMENTS_FORWARDCPT_H
#define EXPERIMENTS_FORWARDCPT_H

#include "BaseCPT.h"
using namespace std;


class ForwardCPT: public BaseCPT {
public:
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
    static ForwardCPT& getInstance(string filePath, bool isMetadataFile, int year,
                                   map<int, double> overrides, string instanceKey);

    /**
     * Constructs an empty instance of this class.
     */
    ForwardCPT() = default;

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
    ForwardCPT(string filePath, bool isMetadataFile, int year);

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
    ForwardCPT(string filePath, bool isMetadataFile, int year, map<int, double> overrides):
            ForwardCPT(filePath, isMetadataFile, year) {
        this->overrides = overrides;
    };

    /**
     * Specifies at which bit the generation process should start
     * @return the start bit (0)
     */
    int startBit() { return 0; }

    /**
     * Specifies at which bit the generation process should stop
     * @return the end bit (Constants::VECTOR_SIZE - 1)
     */
    int endBit() { return VECTOR_SIZE - 1; }

    /**
     * Determines whether the traversing of the vector happens from left to right or vice-versa.
     * @return delta (1)
     */
    int bitAdvance() { return 1; }

private:
    /**
     * Finds the index of the two parents (previous round) associated to the given @param{bitId}
     * @param bitId index of the bit whose parents we are looking for.
     * @return a pair of two indices corresponding to the parents' positions in the vector. The first index is always
     * less than the second one.
     */
    pair<int, int> getParentBits(int bitId);

    /**
     * Finds the bit index that corresponds to the other match whose winner will play against the winner of
     * the provided bit index
     * @param bitId index of the bit used as reference
     * @return the index of the other bit
     */
    int getSiblingBit(int bitId);

    /**
     * conditionalCounts keep track of how many times a particular bit was 1 given that both parents (from the
     * previous round) where a particular value. Since there are only two parents the key for this map can have only
     * four different combinations.
     * The size should be of size Constants::VECTOR_SIZE and the i-th element should correspond to the
     * conditional counts for the i-th bit. The bit index is the first key of this map.
     */
    map<int, map<pair<int, int>, int>> conditionalCounts;

    /**
     * parentCounts holds how many times an specific configuration of two parents appeared among
     * the years considered.
     * The i-th element of this vector corresponds to the i-th bit, the counts correspond to two parents but given
     * that the positions are fixed we only need one. We will use the lower index of the two.
     */
    map<int, map<pair<int, int>, int>> parentCounts;
    static map<string, ForwardCPT*> instances;
};


#endif //EXPERIMENTS_FORWARDCPT_H
