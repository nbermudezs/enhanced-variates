/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/7/18
 */

#ifndef EXPERIMENTS_BASECPT_H
#define EXPERIMENTS_BASECPT_H

#include <map>
#include <string>
#include "../Constants.h"
using namespace std;

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
    vector<double> probabilities;
};


#endif //EXPERIMENTS_BASECPT_H
