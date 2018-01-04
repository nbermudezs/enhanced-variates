//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "Bracket.h"

Bracket::Bracket() {

}

Bracket::Bracket(bitset<VECTOR_SIZE> data) {
    this->data = data;
}

Bracket *Bracket::smoothen(Bracket* other) {
    bitset<VECTOR_SIZE> data;
    for (int i = 0; i < VECTOR_SIZE; i++) {
        data[i] = (this->data[i] + other->data[i]) / 2;
    }
    return new Bracket(data);
}
