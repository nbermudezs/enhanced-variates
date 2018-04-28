/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 4/9/18
 */

#ifndef EXPERIMENTS_BRACKETUTILS_H
#define EXPERIMENTS_BRACKETUTILS_H

#include <vector>
#include "../Bracket.h"
using namespace std;

typedef vector<int> SeedVector;

/*
 * Specifies the pair of seeds that match each other on each game.
 * The order corresponds to the order of the bits on each region.
 */
const static pair<int, int> GROUP_SEEDS[] = {
        pair<int, int>(1, 16),
        pair<int, int>(8, 9),
        pair<int, int>(5, 12),
        pair<int, int>(4, 13),
        pair<int, int>(6, 11),
        pair<int, int>(3, 14),
        pair<int, int>(7, 10),
        pair<int, int>(2, 15)
};

/**
 * Reward for the scoring corresponding to every bit
 * of a region (REGION_VECTOR_SIZE size)
 */
const static int REGION_BIT_REWARD[] = {
    10, 10, 10, 10, 10, 10, 10, 10,
    20, 20, 20, 20,
    40, 40,
    80
};

class BracketUtils {
public:
    /**
     * Get the bit position of the next round corresponding to
     * the reference bitId
     * @param bitId reference bit
     * @return next round bit
     */
    static int nextRoundParentBitId(int bitId) {
        int parent;
        if (bitId == 14 || bitId == 29)
            parent = 60;
        else if (bitId == 44 || bitId == 59)
            parent = 61;
        else if (bitId == 60 || bitId == 61)
            parent = 62;
        else {
            int relBit = bitId % 15;
            int regionId = bitId / 15;
            if (relBit >= 0 && relBit < 8) {
                parent = regionId * 15 + 8 + (int) floor(relBit / 2);
            } else if (relBit >= 8 && relBit < 12) {
                parent = regionId * 15 + 12 + (int) floor((relBit - 8) / 2);
            } else {
                parent = regionId * 15 + 14;
            }
        }
        return parent;
    }

    /**
     * Get the bit positions corresponding to the previous round
     * given the reference bitId
     * @param bitId reference bit
     * @return a pair of the two bits in the previous round
     */
    static pair<int, int> prevRoundParentBitIds(int bitId) {
        if (bitId == 62) return make_pair(60, 61);
        if (bitId == 61) return make_pair(44, 59);
        if (bitId == 60) return make_pair(14, 29);
        if (bitId % 15 < 8) return make_pair(-1, -1);

        int mod = bitId % 15;
        if (mod == 14) return make_pair(bitId - 2, bitId - 1);

        int factor = bitId / 15;
        int base;
        if (mod < 12) base = (mod % 8) * 2 + 15 * factor;
        else if (mod < 14) base = 8 + (mod % 12) * 2 + 15 * factor;
        return make_pair(base, base + 1);
    };

    /**
     * Converts a bit vector representation into a vector of seeds
     * representing how the seeds moved across the tournament.
     * For the conversion, the vector is assumed in the given format.
     * @param bitRep bit vector representation of the bracket
     * @param format format of the vector. TTT or FFF allowed
     * @return seed vector
     */
    static SeedVector bitsToSeeds(BracketData bitRep, const string format) {
        SeedVector result = SeedVector(VECTOR_SIZE);
        SeedVector regionWinners = {0, 0, 0, 0};

        map<int, int> bitIdToRoundFormat;
        bitIdToRoundFormat[8] = 0;
        bitIdToRoundFormat[9] = 0;
        bitIdToRoundFormat[10] = 0;
        bitIdToRoundFormat[11] = 0;
        bitIdToRoundFormat[12] = 1;
        bitIdToRoundFormat[13] = 1;
        bitIdToRoundFormat[14] = 2;

        for (int region = 0; region < 4; region++) {
            for (int i = 0; i < REGION_VECTOR_SIZE; i++) {
                int bitId = region * REGION_VECTOR_SIZE + i;
                int bitVal = bitRep[VECTOR_SIZE - bitId - 1];

                int seed = 0;

                if (i < 8) {
                    seed = bitVal ? GROUP_SEEDS[i].first : GROUP_SEEDS[i].second;
                } else {
                    if (format[bitIdToRoundFormat[i]] == 'F') {
                        auto prevRoundBitIds = prevRoundParentBitIds(bitId);
                        auto maxParent = result[prevRoundBitIds.first] >= result[prevRoundBitIds.second] ?
                                         result[prevRoundBitIds.first] : result[prevRoundBitIds.second];
                        auto minParent = result[prevRoundBitIds.first] < result[prevRoundBitIds.second] ?
                                         result[prevRoundBitIds.first] : result[prevRoundBitIds.second];
                        seed = bitVal ? minParent : maxParent;
                    } else if (format[bitIdToRoundFormat[i]] == 'T') {
                        auto prevRoundBitIds = prevRoundParentBitIds(bitId);
                        seed = bitVal ? result[prevRoundBitIds.first] : result[prevRoundBitIds.second];
                    }
                }
                result[bitId] = seed;

                if (i == REGION_VECTOR_SIZE - 1)
                    regionWinners[region] = seed;
            }
        }
        // last 3 bits are 0/1 positional. NOT seeds
        result[60] = bitRep[VECTOR_SIZE - 1 - 60];
        result[61] = bitRep[VECTOR_SIZE - 1 - 61];
        result[62] = bitRep[VECTOR_SIZE - 1 - 62];
        return result;
    }

    /**
     * Creates a BracketData representation from the seed movement
     * across the rounds. The vector will be generated using the requested format.
     * @param seeds vector of seeds (size VECTOR_SIZE) of the movements in the tournament
     * @param format format for the generated bracket (TTT or FFF supported)
     * @return bit representation in the requested format
     */
    static BracketData seedsToBits(SeedVector seeds, string format) {
        BracketData result;

        map<int, int> bitIdToRoundFormat;
        bitIdToRoundFormat[8] = 0;
        bitIdToRoundFormat[9] = 0;
        bitIdToRoundFormat[10] = 0;
        bitIdToRoundFormat[11] = 0;
        bitIdToRoundFormat[12] = 1;
        bitIdToRoundFormat[13] = 1;
        bitIdToRoundFormat[14] = 2;

        for (int region = 0; region < 4; region++) {
            for (int i = 0; i < REGION_VECTOR_SIZE; i++) {
                int bitId = region * REGION_VECTOR_SIZE + i;
                if (i < 8) {
                    result[VECTOR_SIZE - 1 - bitId] = seeds[bitId] == GROUP_SEEDS[i].first;
                } else {
                    if (format[bitIdToRoundFormat[i]] == 'F') {
                        auto prevRoundBitIds = prevRoundParentBitIds(bitId);
                        auto favorite = seeds[prevRoundBitIds.first] < seeds[prevRoundBitIds.second] ?
                                        seeds[prevRoundBitIds.first]: seeds[prevRoundBitIds.second];
                        result[VECTOR_SIZE - 1 - bitId] = seeds[bitId] == favorite;
                    } else if (format[bitIdToRoundFormat[i]] == 'T') {
                        auto prevRoundBitIds = prevRoundParentBitIds(bitId);
                        result[VECTOR_SIZE - 1 - bitId] = seeds[bitId] == seeds[prevRoundBitIds.first];
                    }
                }
            }
        }

        result[VECTOR_SIZE - 1 - 60] = seeds[60];
        result[VECTOR_SIZE - 1 - 61] = seeds[61];
        result[VECTOR_SIZE - 1 - 62] = seeds[62];

        return result;
    }

    /**
     * Calculates the score of a bracket based on how the seeds
     * have moved across the rounds.
     * @param ref seed movement for the ground truth
     * @param seeds seed movement for the bracket to be tested
     * @return a vector containing the total score as well as per-round scores
     */
    static vector<int> scoreFromSeeds(SeedVector ref, SeedVector seeds) {
        vector<int> scores = {0, 0, 0, 0, 0, 0, 0};
        for (int region = 0; region < 4; region++) {
            for (int i = 0; i < REGION_VECTOR_SIZE; i++) {
                int bitId = region * REGION_VECTOR_SIZE + i;
                if (seeds[bitId] == ref[bitId]) {
                    scores[6] += REGION_BIT_REWARD[i];

                    int round;
                    if (i < 8) round = 0;
                    else if (i < 12) round = 1;
                    else if (i < 14) round = 2;
                    else round = 3;

                    scores[round] += REGION_BIT_REWARD[i];
                }
            }
        }

        bool firstSemiRight = false;
        if (seeds[60] == ref[60]) {
            if ((ref[60] == 1 && seeds[14] == ref[14]) || (ref[60] == 0 && seeds[29] == ref[29])) {
                firstSemiRight = true;
                scores[6] += 160;
                scores[4] += 160;
            }
        }

        bool secondSemiRight = false;
        if (seeds[61] == ref[61]) {
            if ((ref[61] == 1 && seeds[44] == ref[44]) || (ref[61] == 0 && seeds[59] == ref[59])) {
                secondSemiRight = true;
                scores[6] += 160;
                scores[4] += 160;
            }
        }

        if (seeds[62] == ref[62] && ((seeds[62] == 1 && firstSemiRight) || (seeds[62 == 0] && secondSemiRight))) {
            scores[5] += 320;
            scores[6] += 320;
        }
        return scores;
    }

    /**
     * Converts a given bracket data from the current format to a new format
     * @param data original bit vector representation of the bracket
     * @param currentFormat format of the data.
     * @param newFormat target format
     * @return a bracket (bit representation) using the new format
     */
    static BracketData convertBracket(BracketData data, string currentFormat, string newFormat) {
        auto intermediate = bitsToSeeds(data, currentFormat);
        return seedsToBits(intermediate, newFormat);
    }
};

#endif //EXPERIMENTS_BRACKETUTILS_H
