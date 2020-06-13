#pragma once

namespace stare
{
template<auto X>
struct nttp
{
    using value_type = decltype(X);

    static constexpr value_type value() noexcept
    {
        return X;
    }

    static constexpr bool is_nttp() noexcept
    {
        return true;
    }

    static constexpr bool is_type() noexcept
    {
        return false;
    }

    static constexpr bool is_hkt() noexcept
    {
        return false;
    }
};

template<typename T>
struct type
{
    using value_type = T;

    static constexpr bool is_nttp() noexcept
    {
        return false;
    }

    static constexpr bool is_type() noexcept
    {
        return true;
    }

    static constexpr bool is_hkt() noexcept
    {
        return false;
    }
};

template<template<typename...> typename TT>
struct hkt
{
    template<typename... Ts>
    using value_type = TT<Ts...>;

    static constexpr bool is_nttp() noexcept
    {
        return false;
    }

    static constexpr bool is_type() noexcept
    {
        return false;
    }

    static constexpr bool is_hkt() noexcept
    {
        return true;
    }
};
} // namespace stare