//
// Created by Nestor Bermudez Sarmiento on 1/3/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

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