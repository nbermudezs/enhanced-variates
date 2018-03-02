/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/7/18
 */

#ifndef EXPERIMENTS_BASECPT_H
#define EXPERIMENTS_BASECPT_H

#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/istreamwrapper.h>
#include <fstream>
#include <map>
#include <string>
#include "../Constants.h"
using namespace std;

const int YEARS = 33;

/**
 * Abstract class that defines the methods that a conditional
 * probability table must support to be used for our simulations.
 */
class BaseCPT {
public:
    /**
     * Returns the unconditional probability of the @param{bitId} being 1
     * @param bitId index of the bit. @see Constants::VECTOR_SIZE
     * @return the probability of the @param{bitId} = 1.
     */
    virtual double P(int bitId) = 0;

    /**
     * Returns the conditional probability of the @param{bitId} being 1
     * @param bitId index of the bit. @see Constants::VECTOR_SIZE
     * @param bracket bracket generated so far, the conditional information
     * to find P(bit = 1) will be taken from this.
     * @return the conditional probability of the given bit being 1.
     */
    virtual double P(int bitId, BracketData bracket) = 0;

    /**
     * Returns the unconditional probabilities for every bit
     * @return vector of size Constants::VECTOR_SIZE where the i-th element
     * corresponds to the probability of that bit being a 1.
     */
    vector<double> getUnconditionalProbabilities() {
        return this->probabilities;
    }

    /**
     * Specifies at which bit the generation process should start
     * @return the start bit (0)
     */
    virtual int startBit() = 0;

    /**
     * Specifies at which bit the generation process should stop
     * @return the end bit (Constants::VECTOR_SIZE - 1)
     */
    virtual int endBit() = 0;

    /**
     * Determines whether the traversing of the vector happens from left to right or vice-versa.
     * @return delta (1)
     */
    virtual int bitAdvance() = 0;

protected:
    /**
     * Constructs an empty instance of this class.
     */
    BaseCPT() {
        for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
            this->probabilities.push_back(0.5);
        }
    };

    /**
     * Attributes
     */
    bool isMetadataFile = false;
    map<int, double> overrides;
    /**
     * Holds the prior (unconditional) probabilities of each
     * bit being 1.
     */
    vector<double> probabilities;
};


#endif //EXPERIMENTS_BASECPT_H
