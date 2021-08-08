// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <type_traits>

namespace is_function {
template <typename>
struct PM_traits {};

template <class T, class U>
struct PM_traits<U T::*> { using member_type = U; };
}

namespace is_empty {
struct C { static int m; };
}

int main() {
    // std::integral_constant
    {
        typedef std::integral_constant<int, 2> two_t;
        typedef std::integral_constant<int, 4> four_t;

        static_assert(!std::is_same<two_t, four_t>::value);

        static_assert(two_t::value * 2 == four_t::value);

        enum class my_e { e1, e2 };

        typedef std::integral_constant<my_e, my_e::e1> my_e_e1;
        typedef std::integral_constant<my_e, my_e::e2> my_e_e2;

        static_assert(my_e_e1() == my_e::e1);

        static_assert(!(my_e_e1::value == my_e::e2));

        static_assert(std::is_same<my_e_e2, my_e_e2>::value);
    }

    // std::is_void
    {
        static_assert(std::is_void<void>::value);
        static_assert(!std::is_void<int>::value);
    }

    #ifdef STALIN_CXX_STD_SINCE_14
    // std::is_null_pointer
    {
        static_assert(std::is_null_pointer<decltype(nullptr)>::value);
        static_assert(!std::is_null_pointer<int *>::value);
    }
    #endif

    // std::is_integral
    {
        class A {};
        enum E : int {};

        static_assert(!std::is_integral<A>::value);
        static_assert(!std::is_integral_v<E>);
        static_assert(!std::is_integral_v<float>);
        static_assert(std::is_integral_v<int>);
        static_assert(std::is_integral_v<const int>);
        static_assert(std::is_integral_v<bool>);
    }
    // std::is_floating_point
    {
        class A {};

        static_assert(!std::is_floating_point<A>::value);
        static_assert(std::is_floating_point<float>::value);
        static_assert(!std::is_floating_point<float &>::value);
        static_assert(std::is_floating_point<double>::value);
        static_assert(!std::is_floating_point<double &>::value);
        static_assert(!std::is_floating_point<int>::value);
    }

    // std::is_array
    {
        class A {};

        static_assert(!std::is_array<A>::value);
        static_assert(std::is_array<A[]>::value);
        static_assert(std::is_array<A[3]>::value);
        static_assert(!std::is_array<float>::value);
        static_assert(!std::is_array<int>::value);
        static_assert(std::is_array<int[]>::value);
        static_assert(std::is_array<int[3]>::value);
        //static_assert(!std::is_array<std::array<int, 3>>::value); // Todo: implement array
    }

    // std::is_enum
    {
        class A {};

        enum E {};

        enum class Ec : int {};

        static_assert(!std::is_enum<A>::value);
        static_assert(std::is_enum<E>::value);
        #ifdef STALIN_CXX_STD_SINCE_17
        static_assert(!std::is_enum_v<int>);
        static_assert(std::is_enum_v<Ec>);
        #endif
    }

    // std::is_union
    {
        struct A {};

        typedef union {
            int a;
            float b;
        } B;

        struct C {
            B d;
        };

        static_assert(!std::is_union<A>::value);
        static_assert(std::is_union<B>::value);
        static_assert(!std::is_union<C>::value);
        static_assert(!std::is_union<int>::value);
    }

    // std::is_class
    {
        struct A {};

        class B {};

        enum class C {};

        static_assert(std::is_class<A>::value);
        static_assert(std::is_class<B>::value);
        static_assert(!std::is_class<C>::value);
        static_assert(!std::is_class<int>::value);
    }

    // std::is_function
    {
        struct A {
            int fun() const &;
        };

        int f();

        static_assert(!std::is_function<A>::value);
        static_assert(std::is_function<int(int)>::value);
        static_assert(std::is_function<decltype(f)>::value);
        static_assert(!std::is_function<int>::value);

        using T = is_function::PM_traits<decltype(&A::fun)>::member_type; // T is int() const&
        static_assert(std::is_function<T>::value);
    }

    // std::is_pointer
    {
        class A {};

        static_assert(!std::is_pointer<A>::value);
        static_assert(std::is_pointer<A *>::value);
        static_assert(!std::is_pointer<A &>::value);
        static_assert(!std::is_pointer<int>::value);
        static_assert(std::is_pointer<int *>::value);
        static_assert(std::is_pointer<int **>::value);
        static_assert(!std::is_pointer<int[10]>::value);
        static_assert(!std::is_pointer<std::nullptr_t>::value);
    }

    // std::is_lvalue_reference
    {
        class A {};

        static_assert(!std::is_lvalue_reference<A>::value);
        static_assert(std::is_lvalue_reference<A &>::value);
        static_assert(!std::is_lvalue_reference<A &&>::value);
        static_assert(!std::is_lvalue_reference<int>::value);
        static_assert(std::is_lvalue_reference<int &>::value);
        static_assert(!std::is_lvalue_reference<int &&>::value);
    }

    // std::is_rvalue_reference
    {
        class A {};

        static_assert(!std::is_rvalue_reference<A>::value);
        static_assert(!std::is_rvalue_reference<A &>::value);
        static_assert(std::is_rvalue_reference<A &&>::value);
        static_assert(!std::is_rvalue_reference<int>::value);
        static_assert(!std::is_rvalue_reference<int &>::value);
        static_assert(std::is_rvalue_reference<int &&>::value);
    }

    // std::is_member_object_pointer
    {
        class cls {};

        static_assert(std::is_member_object_pointer<int (cls::*)>::value);
        static_assert(!std::is_member_object_pointer<int (cls::*)()>::value);
    }

    // std::is_member_function_pointer
    {
        class A {
        public:
            void function() {}
            int object;
        };

        static_assert(std::is_member_function_pointer<decltype(&A::function)>::value);
        static_assert(!std::is_member_function_pointer<decltype(&A::object)>::value);
    }

    // std::is_fundamental
    {
        class A {};

        static_assert(!std::is_fundamental<A>::value);
        static_assert(std::is_fundamental<int>::value);
        static_assert(!std::is_fundamental<int &>::value);
        static_assert(!std::is_fundamental<int *>::value);
        static_assert(std::is_fundamental<float>::value);
        static_assert(!std::is_fundamental<float &>::value);
        static_assert(!std::is_fundamental<float *>::value);
    }

    // std::is_arithmetic
    {
        class A {};

        static_assert(!std::is_arithmetic_v<A>);
        static_assert(std::is_arithmetic_v<bool>);
        static_assert(std::is_arithmetic_v<int>);
        static_assert(std::is_arithmetic_v<int const>);
        static_assert(!std::is_arithmetic_v<int &>);
        static_assert(!std::is_arithmetic_v<int *>);
        static_assert(std::is_arithmetic_v<float>);
        static_assert(std::is_arithmetic_v<float const>);
        static_assert(!std::is_arithmetic_v<float &>);
        static_assert(!std::is_arithmetic_v<float *>);
        static_assert(std::is_arithmetic_v<char>);
        static_assert(std::is_arithmetic_v<char const>);
        static_assert(!std::is_arithmetic_v<char &>);
        static_assert(!std::is_arithmetic_v<char *>);
    }

    // std::is_scalar
    {
        class cls {};

        static_assert(std::is_scalar<int>::value);
        static_assert(!std::is_scalar<cls>::value);
    }

    // std::is_object
    {
        class cls {};

        static_assert(std::is_object<int>::value);
        static_assert(!std::is_object<int &>::value);
        static_assert(std::is_object<cls>::value);
        static_assert(!std::is_object<cls &>::value);
    }

    // std::is_compound
    {
        class cls {};

        static_assert(std::is_compound<cls>::value);
        static_assert(!std::is_compound_v<int>);
    }

    // std::is_reference
    {
        class A {};

        static_assert(!std::is_reference<A>::value);
        static_assert(std::is_reference<A &>::value);
        static_assert(std::is_reference<A &&>::value);
        static_assert(!std::is_reference<int>::value);
        static_assert(std::is_reference<int &>::value);
        static_assert(std::is_reference<int &&>::value);
    }

    // std::is_member_pointer
    {
        class cls {};

        static_assert(std::is_member_pointer<int (cls::*)>::value);
        static_assert(!std::is_member_pointer<int>::value);
    }

    // std::is_const
    {
        static_assert(!std::is_const_v<int>);
        static_assert(std::is_const_v<const int>);
        static_assert(!std::is_const_v<const int *>);
        static_assert(std::is_const_v<int *const>);
        static_assert(!std::is_const_v<const int &>);
        #ifdef STALIN_CXX_STD_SINCE_14
        static_assert(std::is_const_v<std::remove_reference_t<const int &>>);
        #endif
    }

    // std::is_volatile
    {
        static_assert(!std::is_volatile<int>::value);
        static_assert(std::is_volatile<volatile int>::value);
    }

    // std::is_trivial
    {
        struct A { int m; };

        struct B { B() {}};

        static_assert(std::is_trivial<A>::value);
        static_assert(!std::is_trivial<B>::value);
    }

    // std::is_trivally_copyable
    {
        struct A {
            int m;
        };

        struct B {
            B(B const &) {}
        };

        struct C {
            virtual void foo();
        };

        struct D {
            int m;

            D(D const &) = default; // -> trivially copyable
            D(int x)
                : m(x + 1) {}
        };

        static_assert(std::is_trivially_copyable<A>::value);
        static_assert(!std::is_trivially_copyable<B>::value);
        static_assert(!std::is_trivially_copyable<C>::value);
        static_assert(std::is_trivially_copyable<D>::value);
    }

    // std::is_standard_layout
    {
        struct A { int m; };

        struct B {
            int m1;
        private:
            int m2;
        };

        struct C { virtual void foo(); };

        static_assert(std::is_standard_layout<A>::value);
        static_assert(!std::is_standard_layout<B>::value);
        static_assert(!std::is_standard_layout<C>::value);
    }

    #ifndef STALIN_CXX_STD_SINCE_20
    // std::is_pod
    {
        struct A { int m; };

        struct B {
            int m1;
        private:
            int m2;
        };

        struct C { virtual void foo(); };


        static_assert(std::is_pod<A>::value);
        static_assert(!std::is_pod<B>::value);
        static_assert(!std::is_pod<C>::value);
    }

    // std::is_literal_type
    {
        struct A { int m; };

        struct B { virtual ~B(); };

        static_assert(std::is_literal_type<A>::value);
        static_assert(!std::is_literal_type<B>::value);
    }
    #endif

    #ifdef STALIN_CXX_STD_SINCE_17
    // std::has_unique_object_representations
    {
        struct foo {
            char c;
            float f;
            short st;
            int i;
        };

        struct bar {
            int a;
            int b;
        };

        //static_assert(!std::has_unique_object_representations_v<foo>);
        //static_assert(std::has_unique_object_representations_v<bar>);
    }
    #endif

    // std::is_empty
    {
        struct A {};

        struct B { int m; };

        struct D { virtual ~D(); };

        union E {};

        struct F { [[no_unique_address]] E e; };

        struct G {
            int: 0;
            // C++ standard allow "as a special case, an unnamed bit-field with a width of zero
            // specifies alignment of the next bit-field at an allocation unit boundary.
            // Only when declaring an unnamed bit-field may the width be zero."
        };

        static_assert(std::is_empty<A>::value);
        static_assert(!std::is_empty<B>::value);
        static_assert(std::is_empty<is_empty::C>::value);
        static_assert(!std::is_empty<D>::value);
        static_assert(!std::is_empty<E>::value);
        static_assert(std::is_empty<G>::value);
    }

    // std::is_polymorphic
    {
        struct A { int m; };

        struct B { virtual void foo(); };

        struct C : B {};

        struct D { virtual ~D() = default; };

        static_assert(!std::is_polymorphic<A>::value);
        static_assert(std::is_polymorphic<B>::value);
        static_assert(std::is_polymorphic<C>::value);
        static_assert(std::is_polymorphic<D>::value);
    }

    // std::is_abstract
    {
        struct A { int m; };

        struct B { virtual void foo(); };

        struct C { virtual void foo() = 0; };

        struct D : C {};

        //static_assert(std::is_abstract<A>::value);
        //static_assert(std::is_abstract<B>::value);
        //static_assert(std::is_abstract<C>::value);
        //static_assert(std::is_abstract<D>::value);
    }

    // std::is_final
    {
        class A {};
        class B final {};

        //static_assert(std::is_final<A>::value);
        //static_assert(std::is_final<B>::value);
    }

    // std::is_aggregate
    {
        struct A { int x, y; };
        struct B { B(int, const char*) { } };

        //static_assert(!std::is_aggregate_v<A>);
        //static_assert(std::is_aggregate_v<B>);
    }

    // std::is_signed
    {
        class A {};
        enum B : int {};
        enum class C : int {};

        static_assert(!std::is_signed<A>::value);
        static_assert(std::is_signed<float>::value);
        static_assert(std::is_signed<signed int>::value);
        static_assert(!std::is_signed<unsigned int>::value);
        static_assert(!std::is_signed<B>::value);
        static_assert(!std::is_signed<C>::value);
        static_assert(!std::is_signed_v<bool>);
        static_assert(std::is_signed<signed int>());
        static_assert(!std::is_signed<unsigned int>{});
    }

    // std::is_unsigned
    {
        class A {};
        enum B : unsigned {};
        enum class C : unsigned {};

        static_assert(!std::is_unsigned<A>::value);
        static_assert(!std::is_unsigned<float>::value);
        static_assert(!std::is_unsigned<signed int>::value);
        static_assert(std::is_unsigned<unsigned int>::value);
        static_assert(!std::is_unsigned<B>::value);
        static_assert(!std::is_unsigned<C>::value);
    }

    // std::is_destructible, std::is_trivially_destructible, std::is_nothrow_destructible
    {
        struct Foo {
            std::aligned_storage<8> str;
            ~Foo() noexcept {};
        };
        struct Bar {
            ~Bar() = default;
        };
        struct Indestructible {
            ~Indestructible() = delete;
        };

        static_assert(std::is_destructible<std::aligned_storage<8>>::value);
        static_assert(!std::is_trivially_destructible<Foo>::value);
        static_assert(std::is_nothrow_destructible<Foo>::value);
        static_assert(std::is_trivially_destructible<Bar>::value);
        static_assert(!std::is_destructible<Indestructible>::value);
    }
}
