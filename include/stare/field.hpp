#pragma once

#include <cassert>
#include <cstring>
#include <string_view>
#include <type_traits>

#include "stare/concepts.hpp"
#include "stare/config.hpp"

namespace stare
{
struct field_base
{};

template<typename Class, typename T>
class standard_field : public field_base
{
public:
    using class_type = Class;
    using type       = T;

private:
    std::string_view name_;

    std::size_t offset_;
    std::size_t alignment_;
    bool        no_unique_address_;

public:
    constexpr standard_field(std::string_view name,
                             std::size_t      offset,
                             std::size_t      alignment,
                             bool             no_unique_address) noexcept
        : name_(name), offset_(offset), alignment_(alignment),
          no_unique_address_(no_unique_address)
    {}

    constexpr std::string_view name() const noexcept
    {
        return name_;
    }

    constexpr std::size_t offset() const noexcept
    {
        return offset_;
    }

    constexpr std::size_t alignment() const noexcept
    {
        return alignment_;
    }

    constexpr bool no_unique_address() const noexcept
    {
        return no_unique_address_;
    }
};

template<typename Class, typename T>
class nonstandard_field : public field_base
{
public:
    using class_type = Class;
    using type       = T;

private:
    std::string_view name_;
    std::size_t      alignment_;
    bool             no_unique_address_;

public:
    constexpr nonstandard_field(std::string_view name,
                                std::size_t      alignment,
                                bool             no_unique_address) noexcept
        : name_(name), alignment_(alignment),
          no_unique_address_(no_unique_address)
    {}

    constexpr std::string_view name() const noexcept
    {
        return name_;
    }

    constexpr std::size_t alignment() const noexcept
    {
        return alignment_;
    }

    constexpr bool no_unique_address() const noexcept
    {
        return no_unique_address_;
    }
};

template<typename T>
concept field = stare::detail::derived_from<T, field_base>&& requires
{
    typename T::class_type;
    typename T::type;
};

template<typename Class, field... FieldTs>
class fields_of
{
    static_assert(
        (stare::detail::same_as<Class, typename FieldTs::class_type> && ...));

public:
    using class_type = Class;

private:
    std::tuple<FieldTs...> fields_;

public:
    template<typename... FieldUs>
    constexpr fields_of(FieldUs&&... fields) noexcept
#ifndef STARE_GCC9_WORKAROUND
        requires((stare::detail::constructible_from<FieldTs, FieldUs&&> && ...))
#endif
        : fields_(static_cast<FieldUs&&>(fields)...)
    {
#ifdef STARE_GCC9_WORKAROUND
        static_assert(
            (stare::detail::constructible_from<FieldTs, FieldUs&&> && ...));
#endif
    }

    template<std::size_t I>
    friend constexpr auto
    get(const fields_of<Class, FieldTs...>& fields) noexcept
        requires(I < sizeof...(FieldTs))
    {
        return std::get<I>(fields.fields_);
    }
};
} // namespace stare

namespace std
{
template<typename Class, typename... FieldTs>
struct tuple_size<stare::fields_of<Class, FieldTs...>>
    : std::integral_constant<std::size_t, sizeof...(FieldTs)>
{};
} // namespace std