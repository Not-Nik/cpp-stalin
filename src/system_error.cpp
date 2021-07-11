// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <system_error>

class generic_category : public std::error_category {
    [[nodiscard]] const char *name() const noexcept override {
        return "generic";
    }
};

class system_category : public std::error_category {
    [[nodiscard]] const char *name() const noexcept override {
        return "system";
    }
};

generic_category gc;
system_category sc;

const std::error_category &std::generic_category() noexcept {
    return gc;
}

const std::error_category &std::system_category() noexcept {
    return sc;
}

std::error_code std::make_error_code(errc e) noexcept {
    return error_code(static_cast<int>(e), generic_category());
}

std::error_condition std::make_error_condition(errc e) noexcept {
    return error_condition(static_cast<int>(e), generic_category());
}

void std::error_code::assign(int val, const std::error_category &cat) noexcept {
    value_ = val;
    cat_ = cat;
}

void std::error_code::clear() noexcept {
    value_ = 0;
    cat_ = system_category();
}

std::error_condition std::error_code::default_error_condition() const noexcept {
    return cat_.default_error_condition(value_);
}

bool std::operator==(const error_code &lhs, const error_code &rhs) noexcept {
    return lhs.category() == rhs.category() && lhs.value() == rhs.value();
}

bool std::operator==(const error_condition &lhs, const error_condition &rhs) noexcept {
    return lhs.category() == rhs.category() && lhs.value() == rhs.value();
}

bool std::operator==(const error_code &lhs, const error_condition &rhs) noexcept {
    return lhs.cat_.equivalent(lhs.value_, rhs) || rhs.cat_.equivalent(lhs, rhs.value_);
}

#ifndef STALIN_CXX_STD_SINCE_20
bool std::operator!=(const error_code &lhs, const error_code &rhs) noexcept {
    return !(lhs == rhs);
}

bool std::operator<(const error_code &lhs, const error_code &rhs) noexcept {
    return lhs.category() < rhs.category() || (lhs.category() == rhs.category() && lhs.value() < rhs.value());
}

bool std::operator!=(const error_condition &lhs, const error_condition &rhs) noexcept {
    return !(lhs == rhs);
}

bool std::operator<(const error_condition &lhs, const error_condition &rhs) noexcept {
    return lhs.category() < rhs.category() || lhs.category() == rhs.category() && lhs.value() < rhs.value();
}

bool std::operator==(const error_condition &lhs, const error_code &rhs) noexcept {
    return lhs.cat_.equivalent(rhs, lhs.value_) || rhs.category().equivalent(rhs.value(), lhs);
}

bool std::operator!=(const error_code &lhs, const error_condition &rhs) noexcept { return !(lhs == rhs); }
bool std::operator!=(const error_condition &lhs, const error_code &rhs) noexcept { return !(lhs == rhs); }
#endif

void std::error_condition::assign(int val, const std::error_category &cat) noexcept {
    value_ = val;
    cat_ = cat;
}

void std::error_condition::clear() noexcept {
    value_ = 0;
    cat_ = system_category();
}

