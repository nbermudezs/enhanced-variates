//
// Created by Nestor Bermudez Sarmiento on 1/14/18.
// nab6@illinois.edu, nestor.bermudezs@gmail.com
// University of Illinois at Urbana-Champaign
//

#include "SmoothingTest.h"

void SmoothingTest::run() {
    assert(1 & 1);
    assert(1 & 0 == 0);

    assert(1 | 1);
    assert(0 | 0 == 0);
    assert(1 | 0 == 1);
}
