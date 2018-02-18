/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

/**
 * For some background on why not use rand:
 * https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
 * http://www.pcg-random.org/posts/cpp-seeding-surprises.html
 *
 * Also for differences between the random generator engines:
 * https://stackoverflow.com/questions/26475595/pseudo-random-number-generator-gives-same-first-output-but-then-behaves-as-expec
 **/

#include "BracketGenerator.h"

BracketGenerator::BracketGenerator(GenerationDirection generationDirection, string format, int year) {
    map<int, double> overrides;
//    for (int i = 0; i < VECTOR_SIZE; i++)
//        if (i < 60 && (i % 15 == 0 || i % 15 == 7 || i % 15 == 5 || i % 15 == 3))
//            overrides[i] = 1.;
    if (generationDirection == GenerationDirection::FORWARD) {
        cpt = &ForwardCPT::getInstance(
                BRACKET_METADATA_FOLDER + "/" + format + "/allBrackets" + format + ".json",
                false,
                year,
                overrides,
                format);
    } else {
        cpt = &BackwardCPT::getInstance(
                BRACKET_METADATA_FOLDER + "/" + format + "/allBrackets" + format + ".json",
                false,
                year,
                overrides,
                format);
    }


    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = minstd_rand0(seed);
}

Bracket* BracketGenerator::get() {
    BracketData data;
    int startBit = cpt->startBit();
    int delta = cpt->bitAdvance();
    int endBit = cpt->endBit() + delta;

    for (int matchId = startBit; matchId != endBit; matchId = matchId + delta) {
        float p = cpt->P(matchId, data);
        int value = distribution(generator) < p ? 1 : 0;
        if (value) {
            bitOnCounts[matchId]++;
        }
        data[VECTOR_SIZE - matchId - 1] = value;
    }
    return new Bracket(data);
}

Bracket *BracketGenerator::get(bool antitheticEnabled, GeneratorConfig config, vector<VariateMethod> variates) {
    BracketData data;
    int startBit = cpt->startBit();
    int delta = cpt->bitAdvance();
    int endBit = cpt->endBit() + delta;

    for (int matchId = startBit; matchId != endBit; matchId = matchId + delta) {
        int value = getMatchResult(data, antitheticEnabled, matchId, config, variates);
        if (value) {
            bitOnCounts[matchId]++;
        }
        data[matchId] = value;
    }
    return new Bracket(data);
}

int BracketGenerator::getMatchResult(BracketData data, bool antitheticEnabled, int matchId, GeneratorConfig config, vector<VariateMethod> variates) {
    int seed = config.seeds[matchId];
    VariateMethod type = variates[matchId];
    generator = minstd_rand0(seed);

    float p = cpt->P(matchId, data);
    const float rn = type == VariateMethod::ANTITHETIC && antitheticEnabled ?
                     (1 - distribution(generator)) :
                     distribution(generator);
    return rn < p ? 1 : 0;
}
