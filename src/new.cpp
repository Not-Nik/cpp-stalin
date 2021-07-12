// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <new>

const std::nothrow_t std::nothrow;
std::new_handler handler = nullptr; // todo memory safety

std::new_handler std::get_new_handler() noexcept { return handler; }
std::new_handler std::set_new_handler(std::new_handler new_p) noexcept {
    new_handler t = handler;
    handler = new_p;
    return t;
}

#ifdef STALIN_CXX_STD_SINCE_17
void *std::__new_impl(size_t count, align_val_t al) noexcept {
#else
    void *__new_impl(size_t count) noexcept {
#endif
    if (count == 0)
        ++count; // avoid std::malloc(0) which may return nullptr on success

    #ifdef STALIN_CXX_STD_SINCE_17
    #if __STDC_VERSION__ >= 201112L
    if (void *ptr = aligned_alloc((size_t) al, count))
        return ptr;
    #else
    if (void *ptr = __aligned_alloc(count, (size_t) al))
        return ptr;
    #endif
    #else
    if (void *ptr = malloc(count))
        return ptr;
    #endif
    if (handler) {
        handler();
        __new_impl(count
            #ifdef STALIN_CXX_STD_SINCE_17
                   , al
            #endif
                   );
    }
    return nullptr;
}

STALIN_NODISCARD_SINCE_20 void *operator new(std::size_t count) {
    if (void *r = std::__new_impl(count))
        return r;
    throw std::bad_alloc();
}

STALIN_NODISCARD_SINCE_20 void *operator new[](std::size_t count) {
    if (void *r = std::__new_impl(count))
        return r;
    throw std::bad_alloc();
}

STALIN_NODISCARD_SINCE_20 void *operator new(std::size_t count, const std::nothrow_t &tag) noexcept {
    return std::__new_impl(count);
}

STALIN_NODISCARD_SINCE_20 void *operator new[](std::size_t count, const std::nothrow_t &tag) noexcept {
    return std::__new_impl(count);
}

STALIN_NODISCARD_SINCE_20 void *operator new(std::size_t count, void *ptr) noexcept {
    return std::__new_impl(count);
}

STALIN_NODISCARD_SINCE_20 void *operator new[](std::size_t count, void *ptr) noexcept {
    return std::__new_impl(count);
}

#ifdef STALIN_CXX_STD_SINCE_17
[[nodiscard]] void *operator new(std::size_t count, std::align_val_t al) {
    if (void *r = std::__new_impl(count, al))
        return r;
    throw std::bad_alloc();
}

[[nodiscard]] void *operator new[](std::size_t count, std::align_val_t al) {
    if (void *r = std::__new_impl(count, al))
        return r;
    throw std::bad_alloc();
}

[[nodiscard]] void *operator new(std::size_t count, std::align_val_t al, const std::nothrow_t &) noexcept {
    return std::__new_impl(count, al);
}

[[nodiscard]] void *operator new[](std::size_t count, std::align_val_t al, const std::nothrow_t &) noexcept {
    return std::__new_impl(count, al);
}
#endif

void operator delete(void *ptr) noexcept { std::free(ptr); }
void operator delete[](void *ptr) noexcept { std::free(ptr); }

void operator delete(void *ptr, const std::nothrow_t &tag) noexcept { std::free(ptr); }
void operator delete[](void *ptr, const std::nothrow_t &tag) noexcept { std::free(ptr); }

void operator delete(void *ptr, void *place) noexcept {}
void operator delete[](void *ptr, void *place) noexcept {}

#ifdef STALIN_CXX_STD_SINCE_14
void operator delete(void *ptr, std::size_t sz) noexcept { std::free(ptr); }
void operator delete[](void *ptr, std::size_t sz) noexcept { std::free(ptr); }
#endif

#ifdef STALIN_CXX_STD_SINCE_17
void operator delete(void *ptr, std::align_val_t al) noexcept { std::__aligned_free(ptr); }
void operator delete[](void *ptr, std::align_val_t al) noexcept { std::__aligned_free(ptr); }

void operator delete(void *ptr, std::size_t sz, std::align_val_t al) noexcept { std::free(ptr); }
void operator delete[](void *ptr, std::size_t sz, std::align_val_t al) noexcept { std::free(ptr); }

void operator delete(void *ptr, std::align_val_t al, const std::nothrow_t &tag) noexcept { std::__aligned_free(ptr); }
void operator delete[](void *ptr, std::align_val_t al, const std::nothrow_t &tag) noexcept { std::__aligned_free(ptr); }
#endif
