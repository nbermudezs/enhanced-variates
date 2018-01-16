//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Bracket.h"

Bracket::Bracket(BracketData data) {
    this->data = data;
}

Bracket *Bracket::smoothen(Bracket* other) {
    BracketData smoothenData;
    for (int i = 0; i < VECTOR_SIZE; i++) {
        smoothenData[i] = (this->data[i] + other->data[i]) / 2.;
    }
    return new Bracket(smoothenData);
}
