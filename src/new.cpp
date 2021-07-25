// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <new>
#include <cstdlib>
#include <type_traits>

const std::nothrow_t std::nothrow;
std::new_handler handler = nullptr; // todo memory safety

std::new_handler std::get_new_handler() noexcept { return handler; }
std::new_handler std::set_new_handler(std::new_handler new_p) noexcept {
    new_handler t = handler;
    handler = new_p;
    return t;
}

void *__aligned_alloc(size_t count, size_t al) noexcept {
    size_t offset = sizeof(void *) + (size_t) al - 1;
    size_t space = count + offset;
    if (void *ptr = malloc(space)) {
        void *orig = ptr;
        if (!std::align((size_t) al, 0, ptr, space)) { // this directly overwrites ptr
            free(orig);
            return nullptr;
        }
        ((void **) ptr)[-1] = orig; // save orig right before ptr
        return ptr;
    }
    return nullptr;
}

void __aligned_free(void *p) {
#if __STDC_VERSION__ >= 201112L
    free(p);
#else
    free(((void **) p)[-1]); // free previously saved orig
#endif
}

#ifdef STALIN_CXX_STD_SINCE_17
void *__new_impl(size_t count, std::align_val_t al = (std::align_val_t) __STDCPP_DEFAULT_NEW_ALIGNMENT__) noexcept {
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
    if (void *r = __new_impl(count))
        return r;
    throw std::bad_alloc();
}

STALIN_NODISCARD_SINCE_20 void *operator new[](std::size_t count) {
    if (void *r = __new_impl(count))
        return r;
    throw std::bad_alloc();
}

STALIN_NODISCARD_SINCE_20 void *operator new(std::size_t count, STALIN_NONSTRICT_MAYBE_UNUSED const std::nothrow_t &tag) noexcept {
    return __new_impl(count);
}

STALIN_NODISCARD_SINCE_20 void *operator new[](std::size_t count, STALIN_NONSTRICT_MAYBE_UNUSED const std::nothrow_t &tag) noexcept {
    return __new_impl(count);
}

STALIN_NODISCARD_SINCE_20 void *operator new(std::size_t count, STALIN_NONSTRICT_MAYBE_UNUSED void *ptr) noexcept {
    return __new_impl(count);
}

STALIN_NODISCARD_SINCE_20 void *operator new[](std::size_t count, STALIN_NONSTRICT_MAYBE_UNUSED void *ptr) noexcept {
    return __new_impl(count);
}

#ifdef STALIN_CXX_STD_SINCE_17
[[nodiscard]] void *operator new(std::size_t count, std::align_val_t al) {
    if (void *r = __new_impl(count, al))
        return r;
    throw std::bad_alloc();
}

[[nodiscard]] void *operator new[](std::size_t count, std::align_val_t al) {
    if (void *r = __new_impl(count, al))
        return r;
    throw std::bad_alloc();
}

[[nodiscard]] void *operator new(std::size_t count, std::align_val_t al, const std::nothrow_t &) noexcept {
    return __new_impl(count, al);
}

[[nodiscard]] void *operator new[](std::size_t count, std::align_val_t al, const std::nothrow_t &) noexcept {
    return __new_impl(count, al);
}
#endif

void operator delete(void *ptr) noexcept { std::free(ptr); }
void operator delete[](void *ptr) noexcept { std::free(ptr); }

void operator delete(void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED const std::nothrow_t &tag) noexcept { std::free(ptr); }
void operator delete[](void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED const std::nothrow_t &tag) noexcept { std::free(ptr); }

// This doing nothing is intended
void operator delete(STALIN_NONSTRICT_MAYBE_UNUSED void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED void *place) noexcept {}
void operator delete[](STALIN_NONSTRICT_MAYBE_UNUSED void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED void *place) noexcept {}

#ifdef STALIN_CXX_STD_SINCE_14
void operator delete(void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED std::size_t sz) noexcept { std::free(ptr); }
void operator delete[](void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED std::size_t sz) noexcept { std::free(ptr); }
#endif

#ifdef STALIN_CXX_STD_SINCE_17
void operator delete(void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED std::align_val_t al) noexcept { __aligned_free(ptr); }
void operator delete[](void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED std::align_val_t al) noexcept { __aligned_free(ptr); }

void operator delete(void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED std::size_t sz, STALIN_NONSTRICT_MAYBE_UNUSED std::align_val_t al) noexcept { std::free(ptr); }
void operator delete[](void *ptr, STALIN_NONSTRICT_MAYBE_UNUSED std::size_t sz, STALIN_NONSTRICT_MAYBE_UNUSED std::align_val_t al) noexcept { std::free(ptr); }

void operator delete(void *ptr,
                     STALIN_NONSTRICT_MAYBE_UNUSED std::align_val_t al,
                     STALIN_NONSTRICT_MAYBE_UNUSED const std::nothrow_t &tag) noexcept { __aligned_free(ptr); }
void operator delete[](void *ptr,
                       STALIN_NONSTRICT_MAYBE_UNUSED std::align_val_t al,
                       STALIN_NONSTRICT_MAYBE_UNUSED const std::nothrow_t &tag) noexcept { __aligned_free(ptr); }
#endif
