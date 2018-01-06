//
// Created by Nestor Bermudez Sarmiento on 1/4/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "BitsetTest.h"

void BitsetTest::run() {
    bitset<5> data;

    assert(data.to_string() == "00000");

    data[0] = 1;
    assert(data.to_string() == "00001");
}
