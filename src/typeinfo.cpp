// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <typeinfo>

bool std::type_info::before(const std::type_info &rhs) const noexcept {
    return this < &rhs;
}

size_t std::type_info::hash_code() const noexcept {
    return (size_t) this;
}

const char *std::type_info::name() const noexcept {
    if (typename_[0] == 0) {
        auto pos = (uintptr_t) this;

        char *str = (char *) typename_; // evil anti-const hack

        for (unsigned long i = 0; i < sizeof(uintptr_t); i++) {
            str[0] = (char) (pos >> (i*8));
        }
        str[sizeof(uintptr_t)] = 0;
    }

    return typename_;
}
