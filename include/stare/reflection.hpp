#pragma once

#include <cassert>
#include <type_traits>
#include <utility>

#include "stare/field.hpp"
#include "stare/nameof.hpp"

namespace stare
{
template<class... Ts>
struct type_list
{
    template<typename U>
    static constexpr type_list<Ts..., U> push_back() noexcept
    {
        return {};
    }

    template<typename U>
    static constexpr type_list<U, Ts...> push_front() noexcept
    {
        return {};
    }
};

template<typename... Ts>
struct bases
{};

template<typename... Ts>
struct fields
{
    template<typename U>
    using tuple_type = std::tuple<stare::field<U, Ts>...>;

    template<typename U, typename... Args>
    static constexpr auto push_field(tuple_type<U>&& fields,
                                     Args&&... args) noexcept
    {
        using field_type = decltype(
            stare::field(std::in_place_type<U>, static_cast<Args&&>(args)...));

        return std::apply(
            [&](stare::field<U, Ts>&&... fields) {
                return std::tuple<stare::field<U, Ts>..., field_type>(
                    std::move(fields)...,
                    field_type(std::in_place_type<U>,
                               static_cast<Args&&>(args)...));
            },
            std::move(fields));
    }
};

template<typename T, typename Fields>
class reflection;

template<typename T, typename... Fields>
class reflection<T, fields<Fields...>>
{
    using reflected_type = T;

private:
    using fields_tuple = typename fields<Fields...>::tuple_type<reflected_type>;

private:
    [[no_unique_address]] fields_tuple fields_;

public:
    constexpr reflection(std::in_place_type_t<T>, fields_tuple fields) noexcept
        : fields_(std::move(fields))
    {}

    constexpr std::string_view name() const noexcept
    {
        return stare::nameof_type<reflected_type>();
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

template<typename T, typename Fields>
class reflection_builder;

template<typename T, typename... Fields>
class reflection_builder<T, fields<Fields...>>
{
public:
    using reflected_type = T;

private:
    using fields_tuple = typename fields<Fields...>::tuple_type<reflected_type>;

private:
    [[no_unique_address]] fields_tuple fields_;

public:
    constexpr reflection_builder(std::in_place_type_t<reflected_type>,
                                 fields_tuple fields) noexcept
        : fields_(std::move(fields))
    {}

public:
    reflection_builder() = default;

    template<typename U>
    constexpr auto field(std::string_view name,
                         std::size_t      offset,
                         std::size_t      align             = alignof(U),
                         bool             no_unique_address = false) && noexcept
    {
        using field_type = stare::field<T, U>;
        return reflection_builder<T, fields<Fields..., U>>(
            std::in_place_type<T>,
            fields<Fields...>::template push_field<T>(std::move(fields_),
                                                      std::in_place_type<U>,
                                                      name,
                                                      offset,
                                                      align,
                                                      no_unique_address));
    }

    constexpr auto build() && noexcept
    {
        return reflection<T, fields<Fields...>>(std::in_place_type<T>,
                                                std::move(fields_));
    }
};

template<typename T>
constexpr auto make_reflection_for() -> reflection_builder<T, fields<>>
{
    return {};
}
} // namespace stare