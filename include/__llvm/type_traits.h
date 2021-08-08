// cpp-stalin (c) Nikolas Wipper 2021

#ifndef CPP_STALIN_INCLUDE___LLVM_TYPE_TRAITS_H_
#define CPP_STALIN_INCLUDE___LLVM_TYPE_TRAITS_H_

#include "__config"

template <class T>
struct is_class;
template <class T>
struct is_scalar;
template <class T>
struct remove_all_extents;
template <class T>
struct is_trivially_default_constructible;
template <class T>
struct is_trivially_copy_constructible;
template <class T>
struct is_trivially_copy_assignable;
template <class T>
struct is_trivially_destructible;
template <class T>
struct underlying_type;
template <class T>
struct is_enum;
template <class From, class To>
struct is_convertible;

template <class T>
struct add_cv;

template <class T>
struct add_const;

template <class T>
struct add_volatile;

template <class T>
struct add_lvalue_reference;

template <class T>
struct add_rvalue_reference;

template <class T>
struct remove_reference;

template <class T>
struct is_reference;

template <class... T>
struct common_type;

template <class T> inline constexpr bool is_enum_v = is_enum<T>::value;
template <class From, class To> inline constexpr bool is_convertible_v = is_convertible<From, To>::value;
template <class T> using underlying_type_t = typename underlying_type<T>::type;
template <class T> using add_cv_t = typename add_cv<T>::type;
template <class T> using add_const_t = typename add_const<T>::type;
template <class T> using add_volatile_t = typename add_volatile<T>::type;
template <class T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template <class T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
template <class T> using remove_reference_t = typename remove_reference<T>::type;
template <class T> inline constexpr bool is_reference_v = is_reference<T>::value;

// This project uses a heavily modified part of the
// LLVM-projects "libcxx" which is licensed under
// the Apache License Version 2.0. A copy of the
// APL is located in the "LICENSE.apl" file in this
// subdirectory. Read the "README" file for more
// information

//===------------------------ type_traits ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

template <class T>
struct __libcpp_is_union : public false_type {};
template <class T>
struct is_union : public __libcpp_is_union<typename remove_cv<T>::type> {};

template <class T>
struct is_trivially_copyable : integral_constant<bool, is_scalar<typename remove_all_extents<T>::type>::value> {};

template <class _Tp>
struct is_standard_layout : integral_constant<bool, is_scalar<typename remove_all_extents<_Tp>::type>::value> {};

#ifndef STALIN_CXX_STD_SINCE_20
template <class T>
struct is_pod : public integral_constant<bool,
                                         is_trivially_default_constructible<T>::value && is_trivially_copy_constructible<T>::value
                                             && is_trivially_copy_assignable<T>::value && is_trivially_destructible<T>::value> {
};
#endif

template <class _Tp>
struct __is_empty1 : public _Tp { double __lx; };
struct __is_empty2 { double __lx; };
template <class _Tp, bool = is_class<_Tp>::value>
struct __libcpp_empty : public integral_constant<bool, sizeof(__is_empty1<_Tp>) == sizeof(__is_empty2)> {};
template <class _Tp>
struct __libcpp_empty<_Tp, false> : public false_type {};
template <class _Tp>
struct is_empty : public __libcpp_empty<_Tp> {};

template <class T, class... Args>
struct is_trivially_constructible : false_type {};
template <class T>
struct is_trivially_constructible<T> : integral_constant<bool, is_scalar<T>::value> {};
template <class T>
struct is_trivially_constructible<T, T &&> : integral_constant<bool, is_scalar<T>::value> {};
template <class T>
struct is_trivially_constructible<T, const T &> : integral_constant<bool, is_scalar<T>::value> {};
template <class T>
struct is_trivially_constructible<T, T &> : integral_constant<bool, is_scalar<T>::value> {};

template <class T, class Arg>
struct is_trivially_assignable : public false_type {};
template <class T>
struct is_trivially_assignable<T &, T> : integral_constant<bool, is_scalar<T>::value> {};
template <class T>
struct is_trivially_assignable<T &, T &> : integral_constant<bool, is_scalar<T>::value> {};
template <class T>
struct is_trivially_assignable<T &, const T &> : integral_constant<bool, is_scalar<T>::value> {};
template <class T>
struct is_trivially_assignable<T &, T &&> : integral_constant<bool, is_scalar<T>::value> {};

template <class T>
struct __libcpp_trivial_destructor : public integral_constant<bool, is_scalar<T>::value || is_reference<T>::value> {};
template <class T>
struct is_trivially_destructible : public __libcpp_trivial_destructor<typename remove_all_extents<T>::type> {};
template <class T>
struct is_trivially_destructible<T[]> : public false_type {};

template <class T>
struct has_virtual_destructor : public false_type {};

template <class _Tp, bool = is_enum_v<_Tp> >
struct __is_scoped_enum_helper : false_type {};
template <class _Tp>
struct __is_scoped_enum_helper<_Tp, true> : public bool_constant<!is_convertible_v<_Tp, underlying_type_t<_Tp> > > {};
template <class _Tp>
struct is_scoped_enum : public __is_scoped_enum_helper<_Tp> {};

template <class _Tp, bool = is_enum<_Tp>::value>
struct __underlying_type_impl;
template <class _Tp>
struct __underlying_type_impl<_Tp, false> {};
template <class _Tp>
struct __underlying_type_impl<_Tp, true> { typedef __underlying_type (_Tp) type; };
template <class _Tp>
struct underlying_type : __underlying_type_impl<_Tp, is_enum<_Tp>::value> {};


// ___
#ifdef STALIN_CXX_STD_SINCE_20

template <class T>
struct remove_cvref;

template <class T> using remove_cvref_t = typename remove_cvref<T>::type;

// Let COPYCV(FROM, TO) be an alias for type TO with the addition of FROM's
// top-level cv-qualifiers.
template <class _From, class _To>
struct __copy_cv {
    using type = _To;
};

template <class _From, class _To>
struct __copy_cv<const _From, _To> {
    using type = add_const_t<_To>;
};

template <class _From, class _To>
struct __copy_cv<volatile _From, _To> {
    using type = add_volatile_t<_To>;
};

template <class _From, class _To>
struct __copy_cv<const volatile _From, _To> {
    using type = add_cv_t<_To>;
};

template <class _From, class _To> using __copy_cv_t = typename __copy_cv<_From, _To>::type;

template <class _From, class _To>
struct __copy_cvref {
    using type = __copy_cv_t<_From, _To>;
};

template <class _From, class _To>
struct __copy_cvref<_From &, _To> {
    using type = add_lvalue_reference_t<__copy_cv_t<_From, _To>>;
};

template <class _From, class _To>
struct __copy_cvref<_From &&, _To> {
    using type = add_rvalue_reference_t<__copy_cv_t<_From, _To>>;
};

template <class _From, class _To> using __copy_cvref_t = typename __copy_cvref<_From, _To>::type;

// Let COND_RES(X, Y) be:
template <class _Xp, class _Yp> using __cond_res = decltype(false ? declval<_Xp(&)()>()() : declval<_Yp(&)()>()());

// Let `XREF(A)` denote a unary alias template `T` such that `T<U>` denotes the same type as `U`
// with the addition of `A`'s cv and reference qualifiers, for a non-reference cv-unqualified type
// `U`.
// [Note: `XREF(A)` is `__xref<A>::template __apply`]
template <class _Tp>
struct __xref {
    template <class _Up> using __apply = __copy_cvref_t<_Tp, _Up>;
};

// Given types A and B, let X be remove_reference_t<A>, let Y be remove_reference_t<B>,
// and let COMMON-REF(A, B) be:
template <class _Ap, class _Bp, class _Xp = remove_reference_t<_Ap>, class _Yp = remove_reference_t<_Bp>>
struct __common_ref;

template <class _Xp, class _Yp> using __common_ref_t = typename __common_ref<_Xp, _Yp>::__type;

template <class _Xp, class _Yp> using __cv_cond_res = __cond_res<__copy_cv_t<_Xp, _Yp> &, __copy_cv_t<_Yp, _Xp> &>;


//    If A and B are both lvalue reference types, COMMON-REF(A, B) is
//    COND-RES(COPYCV(X, Y)&, COPYCV(Y, X)&) if that type exists and is a reference type.
template <class _Ap, class _Bp, class _Xp, class _Yp> requires requires { typename __cv_cond_res<_Xp, _Yp>; }
    && is_reference_v<__cv_cond_res<_Xp, _Yp>>
struct __common_ref<_Ap &, _Bp &, _Xp, _Yp> {
    using __type = __cv_cond_res<_Xp, _Yp>;
};

//    Otherwise, let C be remove_reference_t<COMMON-REF(X&, Y&)>&&. ...
template <class _Xp, class _Yp> using __common_ref_C = remove_reference_t<__common_ref_t<_Xp &, _Yp &>> &&;


//    .... If A and B are both rvalue reference types, C is well-formed, and
//    is_convertible_v<A, C> && is_convertible_v<B, C> is true, then COMMON-REF(A, B) is C.
template <class _Ap, class _Bp, class _Xp, class _Yp> requires requires { typename __common_ref_C<_Xp, _Yp>; }
    && is_convertible_v<_Ap &&, __common_ref_C<_Xp, _Yp>> && is_convertible_v<_Bp &&, __common_ref_C<_Xp, _Yp>>
struct __common_ref<_Ap &&, _Bp &&, _Xp, _Yp> {
    using __type = __common_ref_C<_Xp, _Yp>;
};

//    Otherwise, let D be COMMON-REF(const X&, Y&). ...
template <class _Tp, class _Up> using __common_ref_D = __common_ref_t<const _Tp &, _Up &>;

//    ... If A is an rvalue reference and B is an lvalue reference and D is well-formed and
//    is_convertible_v<A, D> is true, then COMMON-REF(A, B) is D.
template <class _Ap, class _Bp, class _Xp, class _Yp> requires requires { typename __common_ref_D<_Xp, _Yp>; }
    && is_convertible_v<_Ap &&, __common_ref_D<_Xp, _Yp>>
struct __common_ref<_Ap &&, _Bp &, _Xp, _Yp> {
    using __type = __common_ref_D<_Xp, _Yp>;
};

//    Otherwise, if A is an lvalue reference and B is an rvalue reference, then
//    COMMON-REF(A, B) is COMMON-REF(B, A).
template <class _Ap, class _Bp, class _Xp, class _Yp>
struct __common_ref<_Ap &, _Bp &&, _Xp, _Yp> : __common_ref<_Bp &&, _Ap &> {};

//    Otherwise, COMMON-REF(A, B) is ill-formed.
template <class _Ap, class _Bp, class _Xp, class _Yp>
struct __common_ref {};

// Note C: For the common_reference trait applied to a parameter pack [...]

template <class...>
struct common_reference;

template <class... _Types> using common_reference_t = typename common_reference<_Types...>::type;

// bullet 1 - sizeof...(T) == 0
template <>
struct common_reference<> {};

// bullet 2 - sizeof...(T) == 1
template <class _Tp>
struct common_reference<_Tp> {
    using type = _Tp;
};

// bullet 3 - sizeof...(T) == 2
template <class _Tp, class _Up>
struct __common_reference_sub_bullet3;
template <class _Tp, class _Up>
struct __common_reference_sub_bullet2 : __common_reference_sub_bullet3<_Tp, _Up> {};
template <class _Tp, class _Up>
struct __common_reference_sub_bullet1 : __common_reference_sub_bullet2<_Tp, _Up> {};

// sub-bullet 1 - If T1 and T2 are reference types and COMMON-REF(T1, T2) is well-formed, then
// the member typedef `type` denotes that type.
template <class _Tp, class _Up>
struct common_reference<_Tp, _Up> : __common_reference_sub_bullet1<_Tp, _Up> {};

template <class _Tp, class _Up> requires is_reference_v<_Tp> && is_reference_v<_Up> && requires { typename __common_ref_t<_Tp, _Up>; }
struct __common_reference_sub_bullet1<_Tp, _Up> {
    using type = __common_ref_t<_Tp, _Up>;
};

// sub-bullet 2 - Otherwise, if basic_common_reference<remove_cvref_t<T1>, remove_cvref_t<T2>, XREF(T1), XREF(T2)>::type
// is well-formed, then the member typedef `type` denotes that type.
template <class, class, template <class> class,
    template <class> class>
struct basic_common_reference {};

template <class _Tp, class _Up> using __basic_common_reference_t = typename basic_common_reference<remove_cvref_t<_Tp>,
                                                                                                   remove_cvref_t<_Up>,
                                                                                                   __xref<_Tp>::template __apply,
                                                                                                   __xref<_Up>::template __apply>::type;

template <class _Tp, class _Up> requires requires { typename __basic_common_reference_t<_Tp, _Up>; }
struct __common_reference_sub_bullet2<_Tp, _Up> {
    using type = __basic_common_reference_t<_Tp, _Up>;
};

// sub-bullet 3 - Otherwise, if COND-RES(T1, T2) is well-formed,
// then the member typedef `type` denotes that type.
template <class _Tp, class _Up> requires requires { typename __cond_res<_Tp, _Up>; }
struct __common_reference_sub_bullet3<_Tp, _Up> {
    using type = __cond_res<_Tp, _Up>;
};

// sub-bullet 4 & 5 - Otherwise, if common_type_t<T1, T2> is well-formed,
//                    then the member typedef `type` denotes that type.
//                  - Otherwise, there shall be no member `type`.
template <class _Tp, class _Up>
struct __common_reference_sub_bullet3 : common_type<_Tp, _Up> {};

// bullet 4 - If there is such a type `C`, the member typedef type shall denote the same type, if
//            any, as `common_reference_t<C, Rest...>`.
template <class _Tp, class _Up, class _Vp, class... _Rest> requires requires { typename common_reference_t<_Tp, _Up>; }
struct common_reference<_Tp, _Up, _Vp, _Rest...> : common_reference<common_reference_t<_Tp, _Up>, _Vp, _Rest...> {};

// bullet 5 - Otherwise, there shall be no member `type`.
template <class...>
struct common_reference {};
#endif

#endif //CPP_STALIN_INCLUDE___LLVM_TYPE_TRAITS_H_
