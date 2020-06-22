#pragma once

#include <type_traits>

#include "stare/config.hpp"
#include "stare/reflection.hpp"

namespace stare
{
template<typename T>
concept adl_reflectable = requires
{
    {
        reflect(std::in_place_type<T>)
    }
    ->stare::declarative_reflection;
};

template<typename T>
concept reflectable = adl_reflectable<T>;

namespace reflect_impl
{
template<std::size_t I>
struct priority_tag : priority_tag<I - 1>
{};

template<>
struct priority_tag<0>
{};

template<stare::reflectable T>
struct fn
{
private:
    // try the adl version first
    static STARE_CONSTEVAL auto impl(priority_tag<2>) noexcept
        -> decltype(reflect(std::in_place_type<T>))
    {
        return reflect(std::in_place_type<T>);
    }

public:
    STARE_CONSTEVAL auto operator()() const noexcept
        -> decltype(impl(priority_tag<2>{}))
    {
        return impl(priority_tag<2>{});
    }
};
} // namespace reflect_impl

inline namespace cpo
{
template<typename T>
inline constexpr auto reflect = reflect_impl::fn<T>{};
}
} // namespace stare