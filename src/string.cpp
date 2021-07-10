// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <string>

using namespace std;

// char_traits<char>

char_traits<char>::char_type *char_traits<char>::assign(char_type *p, size_t n, char_type c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

int char_traits<char>::compare(const char_type *p, const char_type *q, size_t n) {
    while (n--) {
        if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1;
        ++p;
        ++q;
    }
    return 0;
}

const char_traits<char>::char_type *char_traits<char>::find(const char_type *p, size_t n, const char_type &c) {
    for (size_t i = 0; i < n; i++) if (eq(p[i], c)) return &p[i];
    return nullptr;
}

char_traits<char>::char_type *char_traits<char>::move(char_type *dest, const char_type *src, size_t n) {
    char_type t[n];
    for (size_t i = 0; i < n; i++) t[i] = src[i];
    for (size_t i = 0; i < n; i++) dest[i] = t[i];
    return dest;
}

char_traits<char>::char_type *char_traits<char>::copy(char_type *dest, const char_type *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}

// char_traits<wchar_t>

char_traits<wchar_t>::char_type *char_traits<wchar_t>::assign(char_type *p, size_t n, char_type c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

int char_traits<wchar_t>::compare(const char_type *p, const char_type *q, size_t n) {
    while (n--) {
        if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1;
        ++p;
        ++q;
    }
    return 0;
}

const char_traits<wchar_t>::char_type *char_traits<wchar_t>::find(const char_type *p, size_t n, const char_type &c) {
    for (size_t i = 0; i < n; i++) if (eq(p[i], c)) return &p[i];
    return nullptr;
}

wchar_t *char_traits<wchar_t>::move(wchar_t *dest, const wchar_t *src, size_t n) {
    char_type t[n];
    for (size_t i = 0; i < n; i++) t[i] = src[i];
    for (size_t i = 0; i < n; i++) dest[i] = t[i];
    return dest;
}

wchar_t *char_traits<wchar_t>::copy(wchar_t *dest, const wchar_t *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}

// char_traits<char16_t>

size_t char_traits<char16_t>::length(const char16_t *s) {
    size_t len = 0;
    while (!eq(*s++, char_type())) len++;
    return len;
}

char16_t *char_traits<char16_t>::assign(char16_t *p, size_t n, char16_t c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

int char_traits<char16_t>::compare(const char16_t *p, const char16_t *q, size_t n) {
    while (n--) {
        if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1;
        ++p;
        ++q;
    }
    return 0;
}

const char16_t *char_traits<char16_t>::find(const char16_t *p, size_t n, const char16_t &c) {
    for (size_t i = 0; i < n; i++) if (eq(p[i], c)) return &p[i];
    return nullptr;
}

char16_t *char_traits<char16_t>::move(char16_t *dest, const char16_t *src, size_t n) {
    char_type t[n];
    for (size_t i = 0; i < n; i++) t[i] = src[i];
    for (size_t i = 0; i < n; i++) dest[i] = t[i];
    return dest;
}

char16_t *char_traits<char16_t>::copy(char16_t *dest, const char16_t *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}

// char_traits<char16_t>

size_t char_traits<char32_t>::length(const char32_t *s) {
    size_t len = 0;
    while (!eq(*s++, char_type())) len++;
    return len;
}

char32_t *char_traits<char32_t>::assign(char32_t *p, size_t n, char32_t c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

int char_traits<char32_t>::compare(const char32_t *p, const char32_t *q, size_t n) {
    while (n--) {
        if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1;
        ++p;
        ++q;
    }
    return 0;
}

const char32_t *char_traits<char32_t>::find(const char32_t *p, size_t n, const char32_t &c) {
    for (int i = 0; i < n; i++) if (eq(p[i], c)) return &p[i];
    return nullptr;
}

char32_t *char_traits<char32_t>::move(char32_t *dest, const char32_t *src, size_t n) {
    char_type t[n];
    for (size_t i = 0; i < n; i++) t[i] = src[i];
    for (size_t i = 0; i < n; i++) dest[i] = t[i];
    return dest;
}

char32_t *char_traits<char32_t>::copy(char32_t *dest, const char32_t *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}
