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
    int score;
    score = scorer.eval(reference, input);
    assert(score == 1920);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("101111111111111111111111111111110111111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 30);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("011111111111111111111111111111111111111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 30);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 60);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000000000000"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 100);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000000000000"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111110111111"));
    score = scorer.eval(reference, input);
    assert(score == 100);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000001000000"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 180);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000001000100"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 340);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000001000110"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 340);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000001000111"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 660);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001111111111111111111111111111111"));
    input =     bitset<VECTOR_SIZE>(string("111111111111111111111111111111110000000000000000000000000000000"));
    score = scorer.eval(reference, input);
    assert(score == 0);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001111111111111111111111111111111"));
    input =     bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    score = scorer.eval(reference, input);
    assert(score == 320);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110000011100011"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110000011000011"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40 - 80 - 160 - 320);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110000011010011"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40 - 80 - 160 - 320 - 160 - 80);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110000011010010"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40 - 80 - 160 - 320 - 160 - 80);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = bitset<VECTOR_SIZE>(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     bitset<VECTOR_SIZE>(string("110101101000000010110100011000101000010010110110100010110101001"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 160 - 2 * 80 - 4 * 40 - 8 * 20 - 16 * 10);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000001000000000000000100000001000110"));
    input =     bitset<VECTOR_SIZE>(string("011011111111111111111111111111111011111111111111111111111111110"));
    score = scorer.eval(reference, input);
    assert(score == 340);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("100000000000000000000000000000000000000000000000000000000000000"));
    score = scorer.eval(reference, input);
    assert(score == 1910);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000001"));
    score = scorer.eval(reference, input);
    assert(score == 1600);

    reference = bitset<VECTOR_SIZE>(string("100000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000001"));
    score = scorer.eval(reference, input);
    assert(score == 1590);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("100000000000000000000000000000000000000000000000000000000000101"));
    score = scorer.eval(reference, input);
    assert(score == 1430);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("100000000000000000000000000000000000000000000000000000000100101"));
    score = scorer.eval(reference, input);
    assert(score == 1350);

    reference = bitset<VECTOR_SIZE>(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     bitset<VECTOR_SIZE>(string("100000000000000000000000000000001000000000000000000000000100101"));
    score = scorer.eval(reference, input);
    assert(score == 1330);
}
