#pragma once

#include <cassert>
#include <type_traits>
#include <utility>

#include "stare/base.hpp"
#include "stare/concepts.hpp"
#include "stare/field.hpp"
#include "stare/nameof.hpp"

namespace stare
{
namespace detail
{
#define NOEXCEPT_DECLTYPE_RETURN(expr)                                         \
    noexcept(noexcept(expr))->decltype(expr)                                   \
    {                                                                          \
        return expr;                                                           \
    }                                                                          \
    static_assert(true, "force trailing semicolon")

using std::get;
template<std::size_t... Is, typename Tuple, typename F>
constexpr auto unpack_impl(std::index_sequence<Is...>, Tuple&& tup, F&& fn)
    NOEXCEPT_DECLTYPE_RETURN(
        static_cast<F&&>(fn)(get<Is>(static_cast<Tuple&&>(tup))...));

template<typename Tuple, typename F>
constexpr auto unpack(Tuple&& tup, F&& fn) NOEXCEPT_DECLTYPE_RETURN(
    unpack_impl(std::make_index_sequence<std::tuple_size_v<Tuple>>{},
                static_cast<Tuple&&>(tup),
                static_cast<F&&>(fn)));

#undef NOEXCEPT_DECLTYPE_RETURN
} // namespace detail

template<typename... Ts>
struct bases
{};

template<typename... Ts>
struct fields
{};

template<typename T, typename Bases, typename Fields>
class reflection;

template<typename T, typename... Bases, field... Fields>
class reflection<T, bases<Bases...>, fields<Fields...>>
{
public:
    using reflected_type = T;

private:
    [[no_unique_address]] bases_of<T, Bases...>   bases_;
    [[no_unique_address]] fields_of<T, Fields...> fields_;

public:
    constexpr reflection(bases_of<T, Bases...>   bases,
                         fields_of<T, Fields...> fields) noexcept
        : bases_(std::move(bases)), fields_(std::move(fields))
    {}

    constexpr reflection(std::in_place_type_t<T>,
                         bases_of<T, Bases...>   bases,
                         fields_of<T, Fields...> fields) noexcept
        : reflection(std::move(bases), std::move(fields))
    {}

    constexpr std::string_view name() const noexcept
    {
        return stare::nameof_type<reflected_type>();
    }

    constexpr const auto& bases() const noexcept
    {
        return bases_;
    }

    constexpr const auto& fields() const noexcept
    {
        return fields_;
    }

    constexpr bool is_complete() const noexcept
    {
        // TODO some complex sizeof align etc checking
        return false;
    }
};

namespace detail
{
template<typename Reflection>
struct is_reflection : std::false_type
{};

template<typename T, typename... Bases, typename... Fields>
struct is_reflection<
    stare::reflection<T, stare::bases<Bases...>, stare::fields<Fields...>>>
    : std::true_type
{};
} // namespace detail

template<typename Reflection>
concept declarative_reflection = detail::is_reflection<Reflection>::value;

template<typename T, typename Bases, typename Fields>
class reflection_builder;

template<typename T, typename... Bases, typename... Fields>
class reflection_builder<T, bases<Bases...>, fields<Fields...>>
{
public:
    using reflected_type = T;

private:
    [[no_unique_address]] bases_of<T, Bases...>   bases_{};
    [[no_unique_address]] fields_of<T, Fields...> fields_{};

public:
    constexpr reflection_builder(std::in_place_type_t<reflected_type>,
                                 bases_of<T, Bases...>   bases,
                                 fields_of<T, Fields...> fields) noexcept
        : bases_(std::move(bases)), fields_(std::move(fields))
    {}

    reflection_builder() = default;

    template<typename U, typename... Args>
    constexpr auto field(std::in_place_type_t<U>, Args&&... args) && noexcept
        requires(std::is_standard_layout_v<T>&& stare::detail::
                     constructible_from<stare::standard_field<T, U>, Args&&...>)
    {
        return reflection_builder<
            T,
            bases<Bases...>,
            fields<Fields..., stare::standard_field<T, U>>>(
            std::in_place_type<T>,
            std::move(bases_),
            detail::unpack(std::move(fields_), [&](Fields&&... fields) {
                return stare::fields_of<T,
                                        Fields...,
                                        stare::standard_field<T, U>>(
                    static_cast<Fields&&>(fields)...,
                    stare::standard_field<T, U>(static_cast<Args&&>(args)...));
            }));
    }

    template<typename U, typename... Args>
    constexpr auto field(std::in_place_type_t<U>, Args&&... args) && noexcept
        requires(
            !std::is_standard_layout_v<T> &&
            stare::detail::constructible_from<stare::nonstandard_field<T, U>,
                                              Args&&...>)
    {
        return reflection_builder<
            T,
            bases<Bases...>,
            fields<Fields..., stare::nonstandard_field<T, U>>>(
            std::in_place_type<T>,
            std::move(bases_),

            detail::unpack(std::move(fields_), [&](Fields&&... fields) {
                return stare::
                    fields_of<T, Fields..., stare::nonstandard_field<T, U>>(
                        static_cast<Fields&&>(fields)...,
                        stare::nonstandard_field<T, U>(
                            static_cast<Args&&>(args)...));
            }));
    }

    template<typename U>
    constexpr auto base(std::in_place_type_t<U>) && noexcept
    {
        return std::move(*this).template base<U>();
    }

    template<typename U>
    constexpr auto base() && noexcept
    {
        return reflection_builder<T, bases<Bases..., U>, fields<Fields...>>(
            std::in_place_type<T>,
            bases_of<T, Bases..., U>{},
            std::move(fields_));
    }

    constexpr auto build() && noexcept
    {
        return reflection<T, bases<Bases...>, fields<Fields...>>(
            std::in_place_type<T>, std::move(bases_), std::move(fields_));
    }
};

template<typename T>
constexpr auto make_reflection_for() -> reflection_builder<T, bases<>, fields<>>
{
    return {};
}
} // namespace stare