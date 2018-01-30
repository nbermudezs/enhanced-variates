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

Bracket *Bracket::flip(vector<int> positions) {
    BracketData clone(this->data);
    for (auto pos: positions)
        clone[pos] = !clone[pos];
    return new Bracket(clone);
}

Bracket *Bracket::flip(int position) {
    return this->flip(vector<int> { position });
}

void Bracket::addChild(Bracket *child) {
    this->children.push_back(child);
}

void Bracket::setMetadata(vector<int> l1Norms, int score) {
    this->l1Norms = l1Norms;
    this->score = score;
}
