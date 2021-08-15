// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitset>
#include <cassert>

int main() {
    // constructors:
    constexpr std::bitset<4> b1;
    constexpr std::bitset<4> b2{0xA}; // == 0B1010
    //std::bitset<4> b3{"0011"}; // can't be constexpr yet
    //std::bitset<8> b4{"ABBA", /*length*/4, /*0:*/'A', /*1:*/'B'}; // == 0B0000'0110
    std::bitset<4> b3{0b0011};
    std::bitset<8> b4{0b0110};

    // bitsets can be printed out to a stream:
    assert(b1 == 0b0000);
    assert(b2 == 0b1010);
    assert(b3 == 0b0011);
    assert(b4 == 0b00000110);

    // bitset supports bitwise operations:
    b3 |= 0b0100;
    assert(b3 == 0b0111);
    b3 &= 0b0011;
    assert(b3 == 0b0011);
    b3 ^= std::bitset<4>{0b1100};
    assert(b3 == 0b1111);

    // operations on the whole set:
    b3.reset();
    assert(b3 == 0);
    b3.set();
    assert(b3 == 0b1111);
    assert(b3.all() && b3.any() && !b3.none());
    b3.flip();
    assert(b3 == 0);

    // operations on individual bits:
    b3.set(/* position = */ 1, true);
    assert(b3 == 0b0010);
    b3.set(/* position = */ 1, false);
    assert(b3 == 0);
    b3.flip(/* position = */ 2);
    assert(b3 == 0b0100);
    b3.reset(/* position = */ 2);
    assert(b3 == 0);

    // subscript operator[] is supported:
    b3[2] = true;
    assert(true == b3[2]);

    // other operations:
    assert(b3.count() == 1);
    assert(b3.size() == 4);
    assert(b3.to_ullong() == 0b0100ULL);
    //assert(b3.to_string() == "0100");

    std::bitset<8> b{0b01110010};
    assert((b >> 1) == 0b00111001);
    assert((b >> 3) == 0b00001110);
    assert((b >> 5) == 0b00000011);
}
