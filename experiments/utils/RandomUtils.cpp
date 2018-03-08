/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 3/2/18
 */

#include "RandomUtils.h"

static minstd_rand0 generator;
static uniform_real_distribution<float> pU;

unsigned int RandomUtils::getUnseededRandomNumber() {
    static random_device rdev;
    return rdev();
}

double RandomUtils::U() {
    return pU(generator);
}

void RandomUtils::setMasterSeed(unsigned int seed) {
    generator = minstd_rand0(seed);
}

unsigned int RandomUtils::generateMasterSeed() {
    static random_device rdev;
    unsigned int seed = rdev();
    return seed % 2 == 0 ? seed - 1 : seed;
}