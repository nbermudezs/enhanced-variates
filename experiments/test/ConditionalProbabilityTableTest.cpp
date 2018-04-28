/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/24/18
 */

#include "ConditionalProbabilityTableTest.h"

void ConditionalProbabilityTableTest::run() {
    BackwardCPT table(TEST_PATH + "/mocks/bracketsMock.json", false, 2018);
    BracketData refOnes ("111111111111111111111111111111111111111111111111111111111111111");
    BracketData refZeros("000000000000000000000000000000000000000000000000000000000000000");
    double p;

    p = table.P(0, refOnes);
    assert(p == 0.5);

    p = table.P(2, refOnes);
    assert(p == 1/6.);

    p = table.P(2, refZeros);
    assert(p == 0);

    p = table.P(3, refOnes);
    assert(p == 1);

    p = table.P(3, refZeros);
    assert(p == 0);

    p = table.P(29, refOnes);
    assert(p == 1/3.);

    p = table.P(29, refZeros);
    assert(p == 1/5.);

    p = table.P(62, refZeros);
    assert(p == 1/8.);

    p = table.P(62, refOnes);
    assert(p == 1/8.);
}
