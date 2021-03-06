/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 4/10/18
 */

#ifndef EXPERIMENTS_BRACKETUTILSTEST_H
#define EXPERIMENTS_BRACKETUTILSTEST_H

#include <cassert>
#include "../utils/BracketUtils.h"

class BracketUtilsTest {
public:
    static void run() {
        runTTTe2e();
        TTTtoFFF();
        testSeedBasedScoring();
        testTFTToSeeds();
        testTFFToSeeds();
        testTTFToSeeds();
        testConversion();
    }

private:
    static void runTTTe2e() {
        BracketData ref2018TTT("001001110111110101111110001110101011011100111111101111110101010");
        BracketData e2e = BracketUtils::seedsToBits(BracketUtils::bitsToSeeds(ref2018TTT, "TTT"), "TTT");
        assert(ref2018TTT == e2e);
    }

    static void TTTtoFFF() {
        BracketData ref2018FFF("001001111100000101111110110011101011011111101111101111001111010");
        BracketData ref2018TTT("001001110111110101111110001110101011011100111111101111110101010");
        BracketData e2e = BracketUtils::seedsToBits(BracketUtils::bitsToSeeds(ref2018TTT, "TTT"), "FFF");
        assert(ref2018FFF == e2e);
    }

    static void testSeedBasedScoring() {
        BracketData ref("110101001001111101111101001001111111111010100110001011010100101");
        BracketData test("100111111000111111101111010001101111011100100101111111010101110");
        auto scores = BracketUtils::scoreFromSeeds(BracketUtils::bitsToSeeds(ref, "TTT"), BracketUtils::bitsToSeeds(test, "TTT"));
        assert(scores[6] == 1040); // total score
        assert(scores[0] == 180); // R64 score
        assert(scores[1] == 180); // R32 score
        assert(scores[2] == 280); // S16
        assert(scores[3] == 240); // E8
        assert(scores[4] == 160); // F4
        assert(scores[5] == 0);
    }

    static void testTFTToSeeds() {
        SeedVector refSeeds = {
                1, 9, 12, 4, 6, 3, 7, 2, 1, 4, 3, 2, 1, 2, 1,
                1, 8, 5, 4, 11, 3, 7, 2, 1, 4, 11, 2, 4, 11, 4,
                1, 9, 5, 4, 6, 3, 10, 2, 1, 5, 3, 2, 1, 3, 3,
                1, 9, 5, 4, 6, 3, 7, 2, 1, 4, 6, 2, 1, 6, 1,
                1, 1, 0
        };
        BracketData test("100111111000111111101111010001101111011100100101111111010101110");
        auto seeds = BracketUtils::bitsToSeeds(test, "TFT");
        for (int i = 0; i < test.size(); i++) {
            assert(seeds[i] == refSeeds[i]);
        }
    }

    static void testTFFToSeeds() {
        SeedVector refSeeds = {
                1, 9, 12, 4, 6, 3, 7, 2, 1, 4, 3, 2, 1, 2, 1,
                1, 8, 5, 4, 11, 3, 7, 2, 1, 4, 11, 2, 4, 11, 4,
                1, 9, 5, 4, 6, 3, 10, 2, 1, 5, 3, 2, 1, 3, 3,
                1, 9, 5, 4, 6, 3, 7, 2, 1, 4, 6, 2, 1, 6, 1,
                1, 1, 0
        };
        BracketData test("100111111000111111101111010001101111011100100101111111010101110");
        auto seeds = BracketUtils::bitsToSeeds(test, "TFF");
        for (int i = 0; i < test.size(); i++) {
            assert(seeds[i] == refSeeds[i]);
        }
    }

    static void testTTFToSeeds() {
        SeedVector refSeeds = {
                1, 9, 12, 4, 6, 3, 7, 2, 1, 4, 3, 2, 1, 3, 1,
                1, 8, 5, 4, 11, 3, 7, 2, 1, 4, 11, 2, 4, 2, 2,
                1, 9, 5, 4, 6, 3, 10, 2, 1, 5, 3, 2, 1, 2, 2,
                1, 9, 5, 4, 6, 3, 7, 2, 1, 4, 6, 2, 1, 2, 1,
                1, 1, 0
        };
        BracketData test("100111111000111111101111010001101111011100100101111111010101110");
        auto seeds = BracketUtils::bitsToSeeds(test, "TTF");
        for (int i = 0; i < test.size(); i++) {
            assert(seeds[i] == refSeeds[i]);
        }
    }

    static void testConversion() {
        BracketData test("101001111100000101111111010011101011011111101111101111001111010");
        auto step1 = BracketUtils::convertBracket(test, "TTT", "FTT");
        auto step2 = BracketUtils::convertBracket(step1, "FTT", "TFT");
        auto step3 = BracketUtils::convertBracket(step2, "TFT", "TTT");
        assert(test == step3);
    }
};

#endif //EXPERIMENTS_BRACKETUTILSTEST_H
