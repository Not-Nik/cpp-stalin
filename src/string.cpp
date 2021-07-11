// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <string>

using namespace std;

// char_traits<char>

#ifndef STALIN_CXX_STD_SINCE_17
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
#endif

#ifndef STALIN_CXX_STD_SINCE_20
char_traits<char>::char_type *char_traits<char>::assign(char_type *p, size_t n, char_type c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

char_traits<char>::char_type *char_traits<char>::move(char_type *dest, const char_type *src, size_t n) {
    if (dest < src) {
        for (size_t i = 0; i < n; i++) dest[i] = src[i];
    } else {
        for (size_t i = n-1; i >= 0; i--) dest[i] = src[i];
    }
    return dest;
}

char_traits<char>::char_type *char_traits<char>::copy(char_type *dest, const char_type *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}
#endif

// char_traits<wchar_t>

#ifndef STALIN_CXX_STD_SINCE_17
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
#endif

#ifndef STALIN_CXX_STD_SINCE_20
char_traits<wchar_t>::char_type *char_traits<wchar_t>::assign(char_type *p, size_t n, char_type c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

char_traits<wchar_t>::char_type *char_traits<wchar_t>::move(char_type *dest, const char_type *src, size_t n) {
    if (dest < src) {
        for (size_t i = 0; i < n; i++) dest[i] = src[i];
    } else {
        for (size_t i = n-1; i >= 0; i--) dest[i] = src[i];
    }
    return dest;
}

char_traits<wchar_t>::char_type *char_traits<wchar_t>::copy(char_type *dest, const char_type *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}
#endif

// char_traits<char16_t>

#ifndef STALIN_CXX_STD_SINCE_17
size_t char_traits<char16_t>::length(const char16_t *s) {
    size_t len = 0;
    while (!eq(*s++, char_type())) len++;
    return len;
}

int char_traits<char16_t>::compare(const char_type *p, const char_type *q, size_t n) {
    while (n--) {
        if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1;
        ++p;
        ++q;
    }
    return 0;
}

const char_traits<char16_t>::char_type *char_traits<char16_t>::find(const char_type *p, size_t n, const char_type &c) {
    for (size_t i = 0; i < n; i++) if (eq(p[i], c)) return &p[i];
    return nullptr;
}
#endif

#ifndef STALIN_CXX_STD_SINCE_20
char_traits<char16_t>::char_type *char_traits<char16_t>::assign(char_type *p, size_t n, char_type c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

char_traits<char16_t>::char_type *char_traits<char16_t>::move(char_type *dest, const char_type *src, size_t n) {
    if (dest < src) {
        for (size_t i = 0; i < n; i++) dest[i] = src[i];
    } else {
        for (size_t i = n-1; i >= 0; i--) dest[i] = src[i];
    }
    return dest;
}

char_traits<char16_t>::char_type *char_traits<char16_t>::copy(char_type *dest, const char_type *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}
#endif

// char_traits<char32_t>

#ifndef STALIN_CXX_STD_SINCE_17
size_t char_traits<char32_t>::length(const char_type *s) {
    size_t len = 0;
    while (!eq(*s++, char_type())) len++;
    return len;
}

int char_traits<char32_t>::compare(const char_type *p, const char32_t *q, size_t n) {
    while (n--) {
        if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1;
        ++p;
        ++q;
    }
    return 0;
}

const char_traits<char32_t>::char_type *char_traits<char32_t>::find(const char_type *p, size_t n, const char_type &c) {
    for (int i = 0; i < n; i++) if (eq(p[i], c)) return &p[i];
    return nullptr;
}
#endif

#ifndef STALIN_CXX_STD_SINCE_20
char_traits<char32_t>::char_type *char_traits<char32_t>::assign(char_type *p, size_t n, char_type c) {
    for (size_t i = 0; i < n; i++) p[i] = c;
    return p;
}

char_traits<char32_t>::char_type *char_traits<char32_t>::move(char_type *dest, const char_type *src, size_t n) {
    if (dest < src) {
        for (size_t i = 0; i < n; i++) dest[i] = src[i];
    } else {
        for (size_t i = n-1; i >= 0; i--) dest[i] = src[i];
    }
    return dest;
}

char_traits<char32_t>::char_type *char_traits<char32_t>::copy(char_type *dest, const char_type *src, size_t n) {
    for (size_t i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}
#endif
