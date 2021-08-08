// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bit>

int main() {
    //constexpr double f64v = 19880124.0;
    //constexpr auto u64v = std::bit_cast<std::uint64_t>(f64v);

    //constexpr std::uint64_t u64v2 = 0x3fe9000000000000ull;
    //constexpr auto f64v2 = std::bit_cast<double>(u64v2);

    static_assert(!std::has_single_bit((unsigned) 0) == true);
    static_assert(std::has_single_bit((unsigned) 1) == true);
    static_assert(std::has_single_bit((unsigned) 2) == true);
    static_assert(!std::has_single_bit((unsigned) 3) == true);
    static_assert(std::has_single_bit((unsigned) 4) == true);
    static_assert(!std::has_single_bit((unsigned) 5) == true);
    static_assert(!std::has_single_bit((unsigned) 6) == true);
    static_assert(!std::has_single_bit((unsigned) 7) == true);
    static_assert(std::has_single_bit((unsigned) 8) == true);
    static_assert(!std::has_single_bit((unsigned) 9) == true);

    static_assert(std::countl_zero((uint8_t) 0) == 8);
    static_assert(std::countl_zero((uint8_t) 0b11111111) == 0);
    static_assert(std::countl_zero((uint8_t) 0b00011100) == 3);

    static_assert(std::countl_one((uint8_t) 0) == 0);
    static_assert(std::countl_one((uint8_t) 0b11111111) == 8);
    static_assert(std::countl_one((uint8_t) 0b11100011) == 3);

    static_assert(std::countr_zero((uint8_t) 0) == 8);
    static_assert(std::countr_zero((uint8_t) 0b11111111) == 0);
    static_assert(std::countr_zero((uint8_t) 0b00011100) == 2);

    static_assert(std::countr_one((uint8_t) 0) == 0);
    static_assert(std::countr_one((uint8_t) 0b11111111) == 8);
    static_assert(std::countr_one((uint8_t) 0b11100011) == 2);

    static_assert(std::bit_width((unsigned) 0) == 0);
    static_assert(std::bit_width((unsigned) 1) == 1);
    static_assert(std::bit_width((unsigned) 2) == 2);
    static_assert(std::bit_width((unsigned) 3) == 2);
    static_assert(std::bit_width((unsigned) 4) == 3);
    static_assert(std::bit_width((unsigned) 5) == 3);
    static_assert(std::bit_width((unsigned) 6) == 3);
    static_assert(std::bit_width((unsigned) 7) == 3);

    static_assert(std::bit_ceil((unsigned) 0b00000000) == 0b00000001);
    static_assert(std::bit_ceil((unsigned) 0b00000001) == 0b00000001);
    static_assert(std::bit_ceil((unsigned) 0b00000010) == 0b00000010);
    static_assert(std::bit_ceil((unsigned) 0b00000011) == 0b00000100);
    static_assert(std::bit_ceil((unsigned) 0b00000100) == 0b00000100);
    static_assert(std::bit_ceil((unsigned) 0b00000101) == 0b00001000);
    static_assert(std::bit_ceil((unsigned) 0b00000110) == 0b00001000);
    static_assert(std::bit_ceil((unsigned) 0b00000111) == 0b00001000);

    static_assert(std::bit_floor((unsigned) 0b00000000) == 0b00000000);
    static_assert(std::bit_floor((unsigned) 0b00000001) == 0b00000001);
    static_assert(std::bit_floor((unsigned) 0b00000010) == 0b00000010);
    static_assert(std::bit_floor((unsigned) 0b00000011) == 0b00000010);
    static_assert(std::bit_floor((unsigned) 0b00000100) == 0b00000100);
    static_assert(std::bit_floor((unsigned) 0b00000101) == 0b00000100);
    static_assert(std::bit_floor((unsigned) 0b00000110) == 0b00000100);
    static_assert(std::bit_floor((unsigned) 0b00000111) == 0b00000100);
    static_assert(std::bit_floor((unsigned) 0b00001000) == 0b00001000);
    static_assert(std::bit_floor((unsigned) 0b00001001) == 0b00001000);

    constexpr std::uint8_t i = 0b00011101;
    static_assert(std::rotl(i,0) == 0b00011101);
    static_assert(std::rotl(i,1) == 0b00111010);
    static_assert(std::rotl(i,4) == 0b11010001);
    static_assert(std::rotl(i,9) == 0b00111010);
    static_assert(std::rotl(i,-1) == 0b10001110);

    static_assert(std::rotr(i,0) == 0b00011101);
    static_assert(std::rotr(i,1) == 0b10001110);
    static_assert(std::rotr(i,9) == 0b10001110);
    static_assert(std::rotr(i,-1) == 0b00111010);

    static_assert(std::popcount((unsigned) 0b00000000) == 0);
    static_assert(std::popcount((unsigned) 0b11111111) == 8);
    static_assert(std::popcount((unsigned) 0b00011101) == 4);
}
