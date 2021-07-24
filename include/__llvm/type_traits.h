// cpp-stalin (c) Nikolas Wipper 2021

#ifndef CPP_STALIN_INCLUDE___LLVM_TYPE_TRAITS_H_
#define CPP_STALIN_INCLUDE___LLVM_TYPE_TRAITS_H_

#include "__config"

template <class T> struct is_class;
template <class T> struct is_scalar;
template <class T> struct remove_all_extents;
template <class T> struct is_trivially_default_constructible;
template <class T> struct is_trivially_copy_constructible;
template <class T> struct is_trivially_copy_assignable;
template <class T> struct is_trivially_destructible;
template <class T> struct underlying_type;
template <class T> struct is_enum;
template <class From, class To> struct is_convertible;

template <class T> inline constexpr bool is_enum_v = is_enum<T>::value;
template <class From, class To> inline constexpr bool is_convertible_v = is_convertible<From, To>::value;
template <class T> using underlying_type_t = typename underlying_type<T>::type;

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

template <class T> struct __libcpp_is_union : public false_type {};
template <class T> struct is_union : public __libcpp_is_union<typename remove_cv<T>::type> {};

template <class T> struct is_trivially_copyable : integral_constant<bool, is_scalar<typename remove_all_extents<T>::type>::value> {};

template <class _Tp> struct is_standard_layout : integral_constant<bool, is_scalar<typename remove_all_extents<_Tp>::type>::value> {};

#ifndef STALIN_CXX_STD_SINCE_20
template <class T>
struct is_pod : public integral_constant<bool,
                                         is_trivially_default_constructible<T>::value && is_trivially_copy_constructible<T>::value
                                             && is_trivially_copy_assignable<T>::value && is_trivially_destructible<T>::value> {
};
#endif

template <class _Tp> struct __is_empty1 : public _Tp { double __lx; };
struct __is_empty2 { double __lx; };
template <class _Tp, bool = is_class<_Tp>::value>
struct __libcpp_empty : public integral_constant<bool, sizeof(__is_empty1<_Tp>) == sizeof(__is_empty2)> {};
template <class _Tp> struct __libcpp_empty<_Tp, false> : public false_type {};
template <class _Tp> struct is_empty : public __libcpp_empty<_Tp> {};

template <class T, class... Args> struct is_trivially_constructible : false_type {};
template <class T> struct is_trivially_constructible<T> : integral_constant<bool, is_scalar<T>::value> {};
template <class T> struct is_trivially_constructible<T, T &&> : integral_constant<bool, is_scalar<T>::value> {};
template <class T> struct is_trivially_constructible<T, const T &> : integral_constant<bool, is_scalar<T>::value> {};
template <class T> struct is_trivially_constructible<T, T &> : integral_constant<bool, is_scalar<T>::value> {};

template <class T, class Arg> struct is_trivially_assignable : public false_type {};
template <class T> struct is_trivially_assignable<T &, T> : integral_constant<bool, is_scalar<T>::value> {};
template <class T> struct is_trivially_assignable<T &, T &> : integral_constant<bool, is_scalar<T>::value> {};
template <class T> struct is_trivially_assignable<T &, const T &> : integral_constant<bool, is_scalar<T>::value> {};
template <class T> struct is_trivially_assignable<T &, T &&> : integral_constant<bool, is_scalar<T>::value> {};

template <class T> struct __libcpp_trivial_destructor : public integral_constant<bool, is_scalar<T>::value || is_reference<T>::value> {};
template <class T> struct is_trivially_destructible : public __libcpp_trivial_destructor<typename remove_all_extents<T>::type> {};
template <class T> struct is_trivially_destructible<T[]> : public false_type {};

template <class T> struct has_virtual_destructor : public false_type {};

template <class _Tp, bool = is_enum_v<_Tp> > struct __is_scoped_enum_helper : false_type {};
template <class _Tp> struct __is_scoped_enum_helper<_Tp, true> : public bool_constant<!is_convertible_v < _Tp, underlying_type_t<_Tp> > > {};
template <class _Tp> struct is_scoped_enum : public __is_scoped_enum_helper<_Tp> {};

template <class _Tp, bool = is_enum<_Tp>::value> struct __underlying_type_impl;
template <class _Tp> struct __underlying_type_impl<_Tp, false> {};
template <class _Tp> struct __underlying_type_impl<_Tp, true> { typedef __underlying_type (_Tp) type; };
template <class _Tp> struct underlying_type : __underlying_type_impl<_Tp, is_enum<_Tp>::value> {};

#endif //CPP_STALIN_INCLUDE___LLVM_TYPE_TRAITS_H_
