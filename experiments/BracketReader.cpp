//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "BracketReader.h"


Bracket* BracketReader::read(string filepath) {
    bitset<VECTOR_SIZE> data("111101111111011111110111110111010001101010011000001111100101000");
    return new Bracket(data);
}