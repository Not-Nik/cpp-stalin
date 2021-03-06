// cpp-stalin (c) Nikolas Wipper 2021

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

    strcpy(comp_buf, "Second, Line!\n");
    std::cout.write("Second, Line!\n", 14); // this also overwrites the '\n' from endl

    assert(memcmp(cout_buf, comp_buf, 1024) == 0);

    std::cout << std::unitbuf;
    std::cout.write("Please supply some input: ", 26);

    char in_comp[1024];
    memset(in_comp, 0, 1024);

    std::cin.getline(in_comp, 1024);
    std::cout.write(in_comp, strlen(in_comp));
}
