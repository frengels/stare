#pragma once

#include "stare/nameof.hpp"

namespace stare
{
template<class... Ts>
struct type_list
{};

template<class>
struct reflection;

namespace detail
{
template<class T>
struct reflection_interface
{
    /// the type's name as interpreted by the compiler
    constexpr auto internal_name() const noexcept
    {
        return stare::nameof_type<T>();
    }

    constexpr auto bases() const noexcept
    {
        return stare::type_list<>{};
    }

    constexpr auto fields() const noexcept
    {
        return std::make_tuple();
    }
};
} // namespace detail
} // namespace stare