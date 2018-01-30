/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/3/18
 */

#include "BitsetTest.h"
#include "ConditionalProbabilityTableTest.h"
#include "ScorerTest.h"
#include "SmoothingTest.h"

int main() {
    BitsetTest::run();
    ConditionalProbabilityTableTest::run();
    ScorerTest::run();
    SmoothingTest::run();

    return 0;
}