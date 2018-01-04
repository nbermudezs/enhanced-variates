//
// Created by Nestor Bermudez Sarmiento on 1/3/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "ScorerTest.h"

void ScorerTest::run() {
    Scorer scorer;
    bitset<VECTOR_SIZE> reference;
    bitset<VECTOR_SIZE> input;
    int score = scorer.eval(reference, input);
    assert(score == 1920);

    reference[1] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1910);

    reference[1] = 0;
    reference[62] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1600);

    reference[1] = 1;
    reference[62] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1590);

    reference[61] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1430);

    reference[59] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1350);

    reference[32] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1330);

    reference[50] = 1;
    score = scorer.eval(reference, input);
    assert(score == 1290);
}
