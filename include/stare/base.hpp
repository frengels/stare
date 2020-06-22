#pragma once

#include <tuple>
#include <type_traits>

#include "stare/concepts.hpp"

namespace stare
{
template<typename Derived, typename Base>
requires stare::detail::derived_from<Derived, Base> struct base
{
    using type       = Base;
    using class_type = Derived;
};

template<typename Derived, typename... Ts>
class bases_of
{
public:
    using class_type = Derived;

public:
    bases_of() = default;

    constexpr bool all_empty() const noexcept
    {
        return (std::is_empty_v<Ts> && ...);
    }

    template<std::size_t I>
    friend constexpr auto get(const bases_of<Derived, Ts...>&) noexcept
        requires(I < sizeof...(Ts))
    {
        return std::tuple_element_t<I, std::tuple<base<Derived, Ts>...>>{};
    }
};
} // namespace stare

namespace std
{
template<typename Derived, typename... Ts>
struct tuple_size<stare::bases_of<Derived, Ts...>>
    : std::integral_constant<std::size_t, sizeof...(Ts)>
{};
} // namespace std