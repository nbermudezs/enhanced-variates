/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/29/17
 */

#include "Scorer.h"

int Scorer::naive_eval(BracketData reference, BracketData input) {
    int match_value = 320;

    int score = 0;
    for (int i=0; i < VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15 || i == 31) {
            match_value /= 2;
        }
        if (reference[i] == input[i]) {
            score += match_value;
        }
    }
    return score;
}

int Scorer::eval(BracketData reference, BracketData input) {
    int match_value = 320;

    int score = 0;
    for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15 || i == 31) {
            match_value /= 2;
        }
        // check previous rounds
        int j = i;
        bool mismatch = false;
        while (j < VECTOR_SIZE) {
            if (reference[j] != input[j]) {
                mismatch = true;
                break;
            }
            int bracketId = (int) floor(log2(j + 1));
            int withinBracketPos = j - pow(2, bracketId) + 1;
            int withinNextBracketPos = withinBracketPos * 2 + 1;
            if (input[j] == 1) {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 1;
            } else {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 2;
            }
        }
        if (!mismatch)
            score += match_value;
    }
    return score;
}

int Scorer::eval(Bracket* ref, Bracket* input) {
    return Scorer::eval(ref->data, input->data);
}

int Scorer::naive_eval(Bracket* ref, Bracket* input) {
    return Scorer::naive_eval(ref->data, input->data);
}

int Scorer::evalWithRegionGrouping(Bracket* ref, Bracket* input) {
    return Scorer::evalWithRegionGrouping(ref->data, input->data);
}

int Scorer::evalWithRegionGrouping(BracketData ref, BracketData input) {
    int matchValue = 320;

    pair<int, bool> south = Scorer::evalRegion(ref, input, 48);
    pair<int, bool> west = Scorer::evalRegion(ref, input, 33);
    pair<int, bool> east = Scorer::evalRegion(ref, input, 18);
    pair<int, bool> midwest = Scorer::evalRegion(ref, input, 3);

    int score = south.first + west.first + east.first + midwest.first;

    // check semifinals
    if (ref[2] == input[2]) {
        if ((ref[2] == 1 && south.second) || (ref[2] == 0 && west.second)) {
            score += 160;

            // check championship
            if (ref[0] == input[0] && ref[0] == 1) {
                score += 320;
            }
        }
    }

    if (ref[1] == input[1]) {
        if ((ref[1] == 1 && east.second) || (ref[1] == 0 && midwest.second)) {
            score += 160;

            // check championship
            if (ref[0] == input[0] && ref[0] == 0) {
                score += 320;
            }
        }
    }

    return score;
}

pair<int, bool> Scorer::evalRegion(BracketData reference, BracketData input, int offset) {
    int matchValue = 80;
    bool finalsMatch = false;

    int score = 0;
    for (unsigned int i = 0; i < REGION_VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15) {
            matchValue /= 2;
        }
        // check previous rounds
        int j = i;
        bool mismatch = false;
        while (j < REGION_VECTOR_SIZE) {
            if (reference[j + offset] != input[j + offset]) {
                mismatch = true;
                break;
            }
            int bracketId = (int) floor(log2(j + 1));
            int withinBracketPos = j - pow(2, bracketId) + 1;
            int withinNextBracketPos = withinBracketPos * 2 + 1;
            if (input[j + offset] == 1) {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 1;
            } else {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 2;
            }
        }
        if (!mismatch) {
            score += matchValue;
            if (i == 0) {
                finalsMatch = true;
            }
        }
    }
    return pair<int, bool>(score, finalsMatch);
}

int Scorer::l1(BracketData ref, BracketData input) {
    int count = 0;
    for (unsigned int i = 0; i < VECTOR_SIZE; i++)
        count += abs(ref[VECTOR_SIZE - i - 1] - input[VECTOR_SIZE - i - 1]);
    return count;
}

int Scorer::l1(Bracket* ref, Bracket* input) {
    return Scorer::l1(ref->data, input->data);
}

vector<int> Scorer::l1ByRounds(BracketData ref, BracketData input) {
    vector<int> result;

    std::function<bool(int)> round64 = [](int bit) {
        return bit < 60 && bit % 15 < 8;
    };
    std::function<bool(int)> round32 = [](int bit) {
        return bit < 60 && bit % 15 >= 8 && bit % 15 < 12;
    };
    std::function<bool(int)> round16 = [](int bit) {
        return bit < 60 && bit % 15 >= 12 && bit % 15 < 14;
    };
    std::function<bool(int)> regionFinal = [](int bit) {
        return bit < 60 && bit % 15 == 14;
    };
    std::function<bool(int)> semiFinals = [](int bit) {
        return bit == 60 || bit == 61;
    };
    std::function<bool(int)> finals = [](int bit) {
        return bit == 62;
    };
    std::function<bool(int)> all = [](int bit) { return true; };
    vector<std::function<bool(int)>> functions = {round64, round32, round16, regionFinal, semiFinals, finals, all};

    for (auto func: functions) {
        int count = 0;
        for (unsigned int i = 0; i < VECTOR_SIZE; i++)
            if(func(i))
                count += abs(ref[VECTOR_SIZE - i - 1] - input[VECTOR_SIZE - i - 1]);
        result.push_back(count);
    }

    return result;
}

vector<int> Scorer::l1ByRounds(Bracket *ref, Bracket *input) {
    return Scorer::l1ByRounds(ref->data, input->data);
}

vector<int> Scorer::byRound(BracketData ref, BracketData input) {
    vector<int> scoresByRound = {0, 0, 0, 0, 0, 0, 0, 0};

    pair<vector<int>, bool> south = Scorer::scoreRegion(ref, input, 48);
    pair<vector<int>, bool> west = Scorer::scoreRegion(ref, input, 33);
    pair<vector<int>, bool> east = Scorer::scoreRegion(ref, input, 18);
    pair<vector<int>, bool> midwest = Scorer::scoreRegion(ref, input, 3);

    int score = 0;
    for (int i = 0; i < south.first.size(); i++) {
        scoresByRound[i] += south.first[i];
        scoresByRound[i] += west.first[i];
        scoresByRound[i] += east.first[i];
        scoresByRound[i] += midwest.first[i];

        score += south.first[i];
        score += west.first[i];
        score += east.first[i];
        score += midwest.first[i];
    }

    // check semifinals
    if (ref[2] == input[2]) {
        if ((ref[2] == 1 && south.second) || (ref[2] == 0 && west.second)) {
            score += 160;
            scoresByRound[4] += 160;

            // check championship
            if (ref[0] == input[0] && ref[0] == 1) {
                scoresByRound[5] = 320;
                score += 320;
            }
        }
    }

    if (ref[1] == input[1]) {
        if ((ref[1] == 1 && east.second) || (ref[1] == 0 && midwest.second)) {
            score += 160;
            scoresByRound[4] += 160;

            // check championship
            if (ref[0] == input[0] && ref[0] == 0) {
                scoresByRound[5] = 320;
                score += 320;
            }
        }
    }
    scoresByRound[6] = score;

    return scoresByRound;
}

vector<int> Scorer::byRound(Bracket *ref, Bracket *input) {
    return Scorer::byRound(ref->data, input->data);
}

pair<vector<int>, bool> Scorer::scoreRegion(BracketData reference, BracketData input, int offset) {
    vector<int> scores = {0, 0, 0, 0};
    int matchValue = 80;
    bool finalsMatch = false;

    int round = 3;
    for (unsigned int i = 0; i < REGION_VECTOR_SIZE; i++) {
        if (i == 1 || i == 3 || i == 7 || i == 15) {
            matchValue /= 2;
            round -= 1;
        }
        // check previous rounds
        int j = i;
        bool mismatch = false;
        while (j < REGION_VECTOR_SIZE) {
            if (reference[j + offset] != input[j + offset]) {
                mismatch = true;
                break;
            }
            int bracketId = (int) floor(log2(j + 1));
            int withinBracketPos = j - pow(2, bracketId) + 1;
            int withinNextBracketPos = withinBracketPos * 2 + 1;
            if (input[j + offset] == 1) {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 1;
            } else {
                j = pow(2, bracketId + 1) + withinNextBracketPos - 2;
            }
        }
        if (!mismatch) {
            scores[round] += matchValue;
            if (i == 0) {
                finalsMatch = true;
            }
        }
    }
    return pair<vector<int>, bool>(scores, finalsMatch);
}

int Scorer::evalFFF(Bracket *ref, Bracket *input) {
    auto refSeeds = BracketUtils::bitsToSeeds(ref->data, "FFF");
    auto inputSeeds = BracketUtils::bitsToSeeds(input->data, "FFF");
    return BracketUtils::scoreFromSeeds(refSeeds, inputSeeds)[6];
}
