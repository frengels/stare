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
    /// the type's name as interpreted by the compiler.
    /// This name is implementation defined to the specific compiler and cannot
    /// reliably be used for cross compiler operations, you should use the user
    /// defined name() instead.
    constexpr auto internal_name() const noexcept
    {
        return stare::nameof_type<T>();
    }

    /// if no bases are defined this will return an empty type list
    constexpr auto bases() const noexcept
    {
        return stare::type_list<>{};
    }

    /// if no fields are defined this will return an empty tuple
    constexpr auto fields() const noexcept
    {
        return std::make_tuple();
    }
};

template<typename T>
concept reflection_type_complete = requires
{
    ::stare::reflection<T>{};
};
} // namespace detail

template<typename T>
concept reflected = stare::detail::reflection_type_complete<T>;
} // namespace stare