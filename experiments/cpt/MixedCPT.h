/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/28/18
 */

#ifndef EXPERIMENTS_MIXEDCPT_H
#define EXPERIMENTS_MIXEDCPT_H


#include "BaseCPT.h"

class MixedCPT: public BaseCPT {
public:
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
};


#endif //EXPERIMENTS_MIXEDCPT_H
