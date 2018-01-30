/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 12/30/17
 */

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
