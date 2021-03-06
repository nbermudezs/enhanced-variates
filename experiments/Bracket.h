/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

#ifndef EXPERIMENTS_BRACKET_H
#define EXPERIMENTS_BRACKET_H

#include <cereal/types/bitset.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>

#include <bitset>
#include "Constants.h"
using namespace std;


class Bracket {
public:
    BracketData data;
    Bracket(BracketData data);
    Bracket(BracketData data, vector<int> flips);
    Bracket* smoothen(Bracket*);

    /**
     * Stores the indices of the bits that were flipped resulting in this Bracket.
     */
    vector<int> flips;

    /**
     * Creates a new Bracket with the bits flipped in the positions provided
     * @param positions List of positions that will be flipped.
     * @return New Bracket with flipped bits
     */
    Bracket* flip(vector<int> positions);

    /**
     * Creates a new Bracket with a single bit flipped in the specified position
     * @param position Index of the bit to be flipped
     * @return New Bracket with a single bit flipped
     */
    Bracket* flip(int position);

    /**
     * Track the descendants of this bracket resulting
     * from flipping one or more bits
     */
    vector<Bracket*> children;

    /**
     * Adds the provided Bracket as a child of this Bracket
     * @param child Child Bracket
     */
    void addChild(Bracket *child);

    /**
     * Stores the L1 Norms between this Bracket and the reference Bracket used to calculate the norm.
     * The vector contains the L1 Norms for the different rounds in the tournament.
     */
    vector<int> l1Norms;

    /**
     * Stores the ESPN-based score using the reference bracket for calculation.
     */
    int score;

    /**
     * Sets the l1Norm and score attributes of this class.
     * @param l1Norm L1 Norm to be set
     * @param score ESPN-based score to be set
     */
    void setMetadata(vector<int> l1Norms, int score);

    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &ar) {
        ar(cereal::make_nvp("fullvector", data.to_string()));
        ar(CEREAL_NVP(score));
        ar.itsWriter.SetFormatOptions(CEREAL_RAPIDJSON_NAMESPACE::PrettyFormatOptions::kFormatSingleLineArray);
        ar(CEREAL_NVP(l1Norms));
        ar.itsWriter.SetFormatOptions(CEREAL_RAPIDJSON_NAMESPACE::PrettyFormatOptions::kFormatDefault);
        if (children.size()) {
            vector<Bracket> tmp;
            for (auto child: children) tmp.push_back(*child);
            ar(cereal::make_nvp("children", tmp));
        }
    }
};


#endif //EXPERIMENTS_BRACKET_H
