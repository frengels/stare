#pragma once

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