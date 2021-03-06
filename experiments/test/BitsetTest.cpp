/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/4/18
 */

#include "BitsetTest.h"

void BitsetTest::run() {
    bitset<5> data;

    assert(data.to_string() == "00000");

    data[0] = 1;
    assert(data.to_string() == "00001");

    bitset<5> other("10000");
    assert(other[0] == 0);

    bitset<5> assignments;
    assignments[0] = 0.5;
    assert(assignments[0] == 1);
}
