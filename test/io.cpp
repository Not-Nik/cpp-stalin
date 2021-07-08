// metaxx (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <iostream>

#include <cassert>

int main() {
    char cout_buf[1024];
    char comp_buf[1024];

    memset(cout_buf, 0, 1024);
    memset(comp_buf, 0, 1024);

    std::cout.rdbuf()->pubsetbuf(cout_buf, 1024);

    strcpy(comp_buf, "Hello, World!");
    std::cout.write("Hello, World!", 13);

    assert(memcmp(cout_buf, comp_buf, 1024) == 0);

    std::cout << std::endl;

    strcpy(comp_buf, "Second, Line!");
    std::cout.write("Second, Line!", 13);

    assert(memcmp(cout_buf, comp_buf, 1024) == 0);
}
