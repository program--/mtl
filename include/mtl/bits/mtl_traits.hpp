#pragma once

#include <type_traits>

#include <mtl/bits/mtl_cpp.hpp>

namespace mtl {
namespace detail {

#if !MTL_CPP17
template<typename...>
struct conjunction : public std::true_type
{};

template<typename T1>
struct conjunction<T1> : T1
{};

template<typename T1, typename... Ts>
struct conjunction<T1, Ts...>
  : public std::conditional_t<bool(T1::value), conjunction<Ts...>, T1>
{};
#else
using std::conjunction;
#endif

#if !MTL_CPP17
template<typename...>
struct disjunction : public std::false_type
{};

template<typename T1>
struct disjunction<T1> : T1
{};

template<typename T1, typename... Ts>
struct disjunction<T1, Ts...>
  : public std::conditional_t<bool(T1::value), disjunction<Ts...>, T1>
{};
#else
using std::disjunction
#endif

template<typename... Ts>
struct all_integral : conjunction<std::is_integral<Ts>...>
{};

} // namespace detail
} // namespace mtl
