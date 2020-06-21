#pragma once

#include <type_traits>

#include "stare/nameof.hpp"

namespace stare
{
template<typename E>
concept enumeral = std::is_enum_v<E>;

template<enumeral E>
class enum_reflection
{

    constexpr std::string_view name() const noexcept
    {
        return stare::nameof_type<E>();
    }
};

template<enumeral E>
consteval auto reflect_enum() noexcept
{}
} // namespace stare