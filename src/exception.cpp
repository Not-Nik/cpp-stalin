// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <exception>

#include <typeinfo>

std::exception::exception(const std::exception &other) noexcept {
    if (typeid(*this) == typeid(other)) {
        what_ = other.what_;
    }
}

std::exception &std::exception::operator=(const std::exception &other) noexcept {
    if (typeid(*this) == typeid(other)) {
        what_ = other.what_;
    }

    return *this;
}
