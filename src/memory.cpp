// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <memory>

// align is required by new's implementation so its still here in freestanding mode
void *std::align(std::size_t alignment, std::size_t size, void *&ptr, std::size_t &space) {
    if (alignment == 1) return ptr;

    auto c = (uintptr_t) ptr;
    auto end = (uintptr_t) ptr + space;
    size_t space_copy = space;
    // check bounds, and alignment
    for (; (c + size < end) && (c % alignment); c++, space--); // fixme: safe, but slow
    if (c % alignment != 0) return nullptr;
    space = space_copy;
    ptr = (void *) c;
    return ptr;
}
