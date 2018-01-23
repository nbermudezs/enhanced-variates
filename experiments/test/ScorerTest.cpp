//
// Created by Nestor Bermudez Sarmiento on 1/3/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "ScorerTest.h"

void testL1Distance() {
    Scorer scorer;
    BracketData reference;
    BracketData input;
    int score;

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    score = Scorer::l1(reference, input);
    assert(score == 0);

    reference = BracketData(string("000000000000000000000000000000001111111111111111111111111111111"));
    input =     BracketData(string("000000000000000000000000000000001111111111111111111111111111111"));
    score = Scorer::l1(reference, input);
    assert(score == 0);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("010000000000000000000000000000000000000000000000000000000000000"));
    score = Scorer::l1(reference, input);
    assert(score == 1);

    reference = BracketData(string("010000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    score = Scorer::l1(reference, input);
    assert(score == 1);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000000000000000000010"));
    score = Scorer::l1(reference, input);
    assert(score == 1);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("111111111111111111111111111111111111111111111111111111111111111"));
    score = Scorer::l1(reference, input);
    assert(score == 63);
}

void testRegionScorer() {
    Scorer scorer;
    BracketData reference;
    BracketData input;
    pair<int, bool> score;

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000111111111111111000"));
    score = scorer.evalRegion(reference, input, 3);
    assert(score.first == 0);
    assert(!score.second);

    score = scorer.evalRegion(reference, input, 18);
    assert(score.first == 320);
    assert(score.second);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000111111110000000000"));
    score = scorer.evalRegion(reference, input, 3);
    assert(score.first == 0);
    assert(!score.second);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000001000000000000000000000000000000111111110000000000"));
    score = scorer.evalRegion(reference, input, 48);
    assert(score.first == 240);
    assert(!score.second);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000101000000000000000000000000000000111111110000000000"));
    score = scorer.evalRegion(reference, input, 48);
    assert(score.first == 200);
    assert(!score.second);

    reference = BracketData(string("101001111100100110101011000100101110111111111100101001011100111"));
    input =     BracketData(string("110111011101100111111011101000111111111111100110101111010100101"));
    score = scorer.evalRegion(reference, input, 48);
    assert(score.first == 110);
    assert(!score.second);
}

void testEvalWithRegionGrouping() {
    Scorer scorer;
    BracketData reference;
    BracketData input;
    int score;

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000100"));
    input =     BracketData(string("000000000000000111111111111111111111111111111111111101110100100"));
    score = scorer.evalWithRegionGrouping(reference, input);
    assert(score == 320 + 2 * 160 + 320 + 80 + 40 + 20 + 10);

    reference = BracketData(string("101001111100100110101011000100101110111111111100101001011100111"));
    input =     BracketData(string("110111011101100111111011101000111111111111100110101111010100101"));
    score = scorer.evalWithRegionGrouping(reference, input);
    assert(score == 540);
}

void ScorerTest::run() {
    testRegionScorer();
    testEvalWithRegionGrouping();
    testL1Distance();

    Scorer scorer;
    BracketData reference;
    BracketData input;
    int score;
    score = scorer.eval(reference, input);
    assert(score == 1920);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("101111111111111111111111111111110111111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 30);

    reference = BracketData(string("000000000000000000000000000000001000000000000000000000000000000"));
    input =     BracketData(string("011111111111111111111111111111111111111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 30);

    reference = BracketData(string("000000000000000000000000000000001000000000000000000000000000000"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 60);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000000000000"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 100);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000000000000"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111110111111"));
    score = scorer.eval(reference, input);
    assert(score == 100);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000001000000"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 180);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000001000100"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 340);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000001000110"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 340);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000001000111"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111111"));
    score = scorer.eval(reference, input);
    assert(score == 660);

    reference = BracketData(string("000000000000000000000000000000001111111111111111111111111111111"));
    input =     BracketData(string("111111111111111111111111111111110000000000000000000000000000000"));
    score = scorer.eval(reference, input);
    assert(score == 0);

    reference = BracketData(string("000000000000000000000000000000001111111111111111111111111111111"));
    input =     BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    score = scorer.eval(reference, input);
    assert(score == 320);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = BracketData(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     BracketData(string("100011111101100100011101001101111101110100011111110000011100011"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = BracketData(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     BracketData(string("100011111101100100011101001101111101110100011111110000011000011"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40 - 80 - 160 - 320);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = BracketData(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     BracketData(string("100011111101100100011101001101111101110100011111110000011010011"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40 - 80 - 160 - 320 - 160 - 80);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = BracketData(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     BracketData(string("100011111101100100011101001101111101110100011111110000011010010"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 40 - 80 - 160 - 320 - 160 - 80);

    //                                      0                              32              48      56  60
    //                                     |                                |               |       |   | |
    reference = BracketData(string("100011111101100100011101001101111101110100011111110100011100011"));
    input =     BracketData(string("110101101000000010110100011000101000010010110110100010110101001"));
    score = scorer.eval(reference, input);
    assert(score == 1920 - 160 - 2 * 80 - 4 * 40 - 8 * 20 - 16 * 10);

    reference = BracketData(string("000000000000000000000000000000001000000000000000100000001000110"));
    input =     BracketData(string("011011111111111111111111111111111011111111111111111111111111110"));
    score = scorer.eval(reference, input);
    assert(score == 340);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("100000000000000000000000000000000000000000000000000000000000000"));
    score = scorer.eval(reference, input);
    assert(score == 1910);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000000000000000000001"));
    score = scorer.eval(reference, input);
    assert(score == 1600);

    reference = BracketData(string("100000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("000000000000000000000000000000000000000000000000000000000000001"));
    score = scorer.eval(reference, input);
    assert(score == 1590);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("100000000000000000000000000000000000000000000000000000000000101"));
    score = scorer.eval(reference, input);
    assert(score == 1430);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("100000000000000000000000000000000000000000000000000000000100101"));
    score = scorer.eval(reference, input);
    assert(score == 1350);

    reference = BracketData(string("000000000000000000000000000000000000000000000000000000000000000"));
    input =     BracketData(string("100000000000000000000000000000001000000000000000000000000100101"));
    score = scorer.eval(reference, input);
    assert(score == 1330);

    reference = BracketData(string("110101001011111011111111110001011001100110101010110010101100101"));
    input =     BracketData(string("110101001010111001111110100000111011111111111011010110111101011"));
    score = scorer.eval(reference, input);
    assert(score == 480);
}
