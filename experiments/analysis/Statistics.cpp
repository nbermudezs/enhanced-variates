//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Statistics.h"

void Statistics::accountFor(int score, Bracket *bracket) {
    scores[score] = (scores[score] || 0) + 1;
}
