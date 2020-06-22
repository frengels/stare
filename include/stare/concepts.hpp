#pragma once

#if __has_include(<concepts>)
#define STARE_CXX_CONCEPTS
#include <concepts>
#else
#include <type_traits>
#endif

namespace stare
{
namespace detail
{
#ifdef STARE_CXX_CONCEPTS
template<typename Derived, typename Base>
concept derived_from = std::derived_from<Derived, Base>;

template<typename T, typename U>
concept same_as = std::same_as<T, U>;

template<typename T, typename... Args>
concept constructible_from = std::constructible_from<T, Args...>;
#else
template<typename Derived, typename Base>
concept derived_from = std::is_base_of_v<Base, Derived>;

template<typename T, typename U>
concept same_as = std::is_same_v<T, U>&& std::is_same_v<U, T>;

template<typename T, typename... Args>
concept constructible_from = std::is_constructible_v<T, Args...>;
#endif
} // namespace detail
} // namespace stare

#ifdef STARE_CXX_CONCEPTS
#undef STARE_CXX_CONCEPTS
#endif