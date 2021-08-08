// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <limits>

int main() {
    static_assert(std::numeric_limits<bool>::max() == true);
    static_assert(std::numeric_limits<char>::max() == CHAR_MAX);
    static_assert(std::numeric_limits<signed char>::max() == SCHAR_MAX);
    static_assert(std::numeric_limits<unsigned char>::max() == UCHAR_MAX);
    static_assert(std::numeric_limits<wchar_t>::max() == WCHAR_MAX);
    static_assert(std::numeric_limits<char8_t>::max() == UCHAR_MAX);
    static_assert(std::numeric_limits<char16_t>::max() == UINT_LEAST16_MAX);
    static_assert(std::numeric_limits<char32_t>::max() == UINT_LEAST32_MAX);
    static_assert(std::numeric_limits<short>::max() == SHRT_MAX);
    static_assert(std::numeric_limits<unsigned short>::max() == USHRT_MAX);
    static_assert(std::numeric_limits<int>::max() == INT_MAX);
    static_assert(std::numeric_limits<unsigned int>::max() == UINT_MAX);
    static_assert(std::numeric_limits<long>::max() == LONG_MAX);
    static_assert(std::numeric_limits<unsigned long>::max() == ULONG_MAX);
    static_assert(std::numeric_limits<long long>::max() == LONG_LONG_MAX);
    static_assert(std::numeric_limits<unsigned long long>::max() == ULONG_LONG_MAX);
    static_assert(std::numeric_limits<float>::max() == FLT_MAX);
    static_assert(std::numeric_limits<double>::max() == DBL_MAX);
    static_assert(std::numeric_limits<long double>::max() == LDBL_MAX);
    
    static_assert(std::numeric_limits<bool>::min() == false);
    static_assert(std::numeric_limits<char>::min() == CHAR_MIN);
    static_assert(std::numeric_limits<signed char>::min() == SCHAR_MIN);
    static_assert(std::numeric_limits<unsigned char>::min() == 0);
    static_assert(std::numeric_limits<wchar_t>::min() == WCHAR_MIN);
    static_assert(std::numeric_limits<char8_t>::min() == 0);
    static_assert(std::numeric_limits<char16_t>::min() == 0);
    static_assert(std::numeric_limits<char32_t>::min() == 0);
    static_assert(std::numeric_limits<short>::min() == SHRT_MIN);
    static_assert(std::numeric_limits<unsigned short>::min() == 0);
    static_assert(std::numeric_limits<int>::min() == INT_MIN);
    static_assert(std::numeric_limits<unsigned int>::min() == 0);
    static_assert(std::numeric_limits<long>::min() == LONG_MIN);
    static_assert(std::numeric_limits<unsigned long>::min() == 0);
    static_assert(std::numeric_limits<long long>::min() == LONG_LONG_MIN);
    static_assert(std::numeric_limits<unsigned long long>::min() == 0);
    static_assert(std::numeric_limits<float>::min() == FLT_MIN);
    static_assert(std::numeric_limits<double>::min() == DBL_MIN);
    static_assert(std::numeric_limits<long double>::min() == LDBL_MIN);
}
