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
    bool isMetadataFile = false;
    string file = isMetadataFile ?
                  BRACKET_METADATA_FOLDER + "/" + format + "/allBrackets_metadata.json" :
                  BRACKET_METADATA_FOLDER + "/" + format + "/allBrackets" + format + ".json";
    this->tripletCPT = &TripletCPT::getInstance(file,
                                               isMetadataFile,
                                               year,
                                               overrides,
                                               format);
    if (generationDirection == GenerationDirection::FORWARD) {
        cpt = &ForwardCPT::getInstance(
                file,
                isMetadataFile,
                year,
                overrides,
                format);
    } else if (generationDirection == GenerationDirection::BACKWARD){
        cpt = &BackwardCPT::getInstance(
                file,
                isMetadataFile,
                year,
                overrides,
                format);
    } else if (generationDirection == GenerationDirection::BASELINE_4) {
        cpt = &MixedCPT::getInstance(
                file,
                isMetadataFile,
                year,
                overrides,
                format);
    }


    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = minstd_rand0(seed);
}

Bracket* BracketGenerator::get() {
    // TODO: change this to use getRNVector()
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
    // TODO: change this to use getRNVector()
    BracketData data;
    int startBit = cpt->startBit();
    int delta = cpt->bitAdvance();
    int endBit = cpt->endBit() + delta;

    for (int matchId = startBit; matchId != endBit; matchId = matchId + delta) {
        int value = getMatchResult(data, antitheticEnabled, matchId, config, variates);
        if (value) {
            bitOnCounts[matchId]++;
        }
        data[VECTOR_SIZE - matchId - 1] = value;
    }
    return new Bracket(data);
}

Bracket *BracketGenerator::get(GeneratorConfig config) {
    if (config.modelType == ModelType::TRIPLETS) {
        return this->generateWithTriplets(config);
    } else if (config.modelType == ModelType::SINGLE_BIT) {
        return this->generateWithSingleBits(config);
    } else {
        return nullptr;
    }
}

int BracketGenerator::getMatchResult(BracketData data, bool antitheticEnabled, int matchId, GeneratorConfig config, vector<VariateMethod> variates) {
    // TODO: change this to use getRNVector()
    int seed = config.seeds[matchId];
    VariateMethod type = variates[matchId];
    generator = minstd_rand0(seed);

    double p = cpt->P(matchId, data);
    const float rn = type == VariateMethod::ANTITHETIC && antitheticEnabled ?
                     (1 - distribution(generator)) :
                     distribution(generator);
    return rn < p ? 1 : 0;
}

vector<double> BracketGenerator::getRNVector() {
    vector<double> result;

    for (short i = 0; i < VECTOR_SIZE; i++)
        result.push_back(RandomUtils::U());

    return result;
}

Bracket *BracketGenerator::generateWithSingleBits(GeneratorConfig config) {
    double retentionP = config.retentionP;
    BracketData data;
    vector<double> rnVector = this->getRNVector();
    for (IntraVariateGroup group: config.intraVariates) {
        for (auto bit: group[VariateMethod::IID]) {
            double rn = rnVector[bit];
            data[VECTOR_SIZE - bit - 1] = rn < cpt->P(bit, data);
            if (data[VECTOR_SIZE - bit - 1])
                bitOnCounts[bit]++;

            for (auto avBit: group[VariateMethod::ANTITHETIC]) {
                double bitRn = RandomUtils::U() < retentionP ? rn : RandomUtils::U();
                data[VECTOR_SIZE - avBit - 1] = 1 - bitRn < cpt->P(avBit, data);
                if (data[VECTOR_SIZE - avBit - 1])
                    bitOnCounts[avBit]++;
            }

            for (auto crnBit: group[VariateMethod::COMMON]) {
                double bitRn = RandomUtils::U() < retentionP ? rn : RandomUtils::U();
                data[VECTOR_SIZE - crnBit - 1] = bitRn < cpt->P(crnBit, data);
                if (data[VECTOR_SIZE - crnBit - 1])
                    bitOnCounts[crnBit]++;
            }
        }
    }
    return new Bracket(data);
}

Bracket *BracketGenerator::generateWithTriplets(GeneratorConfig config) {
    vector<double> rnVector = this->getRNVector();

    vector<int> indices;
    for (int i = 0; i < VECTOR_SIZE; i++)
        indices.push_back(i);

    double retentionP = config.retentionP;
    BracketData data;
    for (IntraVariateGroup group: config.intraVariates) {
        for (auto bit = VECTOR_SIZE - 1; bit > 0; bit--) {
            if (find(begin(indices), end(indices), bit) == end(indices)) {
                // already filled in, continue
                continue;
            }
            auto parents = this->tripletCPT-> getParentBits(bit);
            if (find(begin(indices), end(indices), parents.first) == end(indices) || find(begin(indices), end(indices), parents.second) == end(indices))
                continue;
            double rn = rnVector[bit];
            if ((bit < 60 && bit % 15 >= 8) || bit >= 60) {
                // use triplets
                bitset<3> triplet = this->tripletCPT->getTriplet(bit, rn);


                int a = triplet[2], b = triplet[1],c = triplet[0];
                data[VECTOR_SIZE - bit - 1] = triplet[2];
                data[VECTOR_SIZE - parents.first - 1] = triplet[1];
                data[VECTOR_SIZE - parents.second - 1] = triplet[0];

                // cout << "setting " << bit << "," << parents.first << "," << parents.second << ":" << triplet << endl;
                // cout << "indices size " << indices.size() << endl;
                indices.erase(find(begin(indices), end(indices), bit));
                indices.erase(find(begin(indices), end(indices), parents.first));
                indices.erase(find(begin(indices), end(indices), parents.second));

                continue;

                for (auto avBit: group[VariateMethod::ANTITHETIC]) {
                    double bitRn = 1 - (RandomUtils::U() < retentionP ? rn : RandomUtils::U());
                    triplet = this->tripletCPT->getTriplet(avBit, bitRn);
                    parents = this->tripletCPT-> getParentBits(avBit);

                    data[VECTOR_SIZE - avBit - 1] = triplet[2];
                    data[VECTOR_SIZE - parents.first - 1] = triplet[1];
                    data[VECTOR_SIZE - parents.second - 1] = triplet[0];

                    remove(begin(indices), end(indices), avBit);
                    remove(begin(indices), end(indices), parents.first);
                    remove(begin(indices), end(indices), parents.second);
                }

                for (auto crnBit: group[VariateMethod::COMMON]) {
                    double bitRn = RandomUtils::U() < retentionP ? rn : RandomUtils::U();
                    triplet = this->tripletCPT->getTriplet(crnBit, bitRn);
                    parents = this->tripletCPT-> getParentBits(crnBit);

                    data[VECTOR_SIZE - crnBit - 1] = triplet[2];
                    data[VECTOR_SIZE - parents.first - 1] = triplet[1];
                    data[VECTOR_SIZE - parents.second - 1] = triplet[0];

                    remove(begin(indices), end(indices), crnBit);
                    remove(begin(indices), end(indices), parents.first);
                    remove(begin(indices), end(indices), parents.second);
                }

                continue;
            }
            data[VECTOR_SIZE - bit - 1] = rn < cpt->P(bit, data);
            if (data[VECTOR_SIZE - bit - 1])
                bitOnCounts[bit]++;

            indices.erase(find(begin(indices), end(indices), bit));

            continue;

            for (auto avBit: group[VariateMethod::ANTITHETIC]) {
                double bitRn = RandomUtils::U() < retentionP ? rn : RandomUtils::U();
                data[VECTOR_SIZE - avBit - 1] = 1 - bitRn < cpt->P(avBit, data);
                if (data[VECTOR_SIZE - avBit - 1])
                    bitOnCounts[avBit]++;
            }

            for (auto crnBit: group[VariateMethod::COMMON]) {
                double bitRn = RandomUtils::U() < retentionP ? rn : RandomUtils::U();
                data[VECTOR_SIZE - crnBit - 1] = bitRn < cpt->P(crnBit, data);
                if (data[VECTOR_SIZE - crnBit - 1])
                    bitOnCounts[crnBit]++;
            }
        }
    }
    return new Bracket(data);
}
