//
// Created by Nestor Bermudez Sarmiento on 12/30/17.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "BracketReader.h"


Bracket* BracketReader::read(string filepath) {
    vector<int> data = {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1,
                        0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0,
                        0, 0, 1, 1, 1, 1, 1, 0,
                        0, 1, 0, 1,
                        0, 0,
                        0};
    return new Bracket(data);
}