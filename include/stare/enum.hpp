#pragma once

#include <array>
#include <string_view>
#include <type_traits>

#include "stare/config.hpp"
#include "stare/nameof.hpp"

namespace stare
{
template<stare::enumeral E>
struct enum_range
{
    static constexpr int min = -128;
    static constexpr int max = 128;
};

template<auto Val>
requires(stare::enumeral<decltype(Val)>) struct enum_entry
{
    static constexpr auto value() noexcept
    {
        return Val;
    }

    static constexpr std::string_view name() noexcept
    {
        return stare::nameof_enum_entry<Val>();
    }
};

/// Obviously inspired by Neargye's magic_enum
template<stare::enumeral E>
class magic_enum_reflection
{
private:
    using underlying_type = std::underlying_type_t<E>;

    static constexpr underlying_type min = [] {
        if constexpr (std::is_unsigned_v<underlying_type>)
        {
            return std::max(0, stare::enum_range<E>::min);
        }
        else
        {
            return stare::enum_range<E>::min;
        }
    }();

    static constexpr underlying_type max = [] {
        if constexpr (std::is_unsigned_v<underlying_type>)
        {
            return std::max(0, stare::enum_range<E>::max);
        }
        else
        {
            return stare::enum_range<E>::max;
        }
    }();

    static constexpr auto count = max - min;

    template<auto Min, typename Int, Int... Is>
    static STARE_CONSTEVAL std::array<std::string_view, sizeof...(Is)>
                           obtain_names(std::integer_sequence<Int, Is...>) noexcept
    {
        return std::array<std::string_view, sizeof...(Is)>{
            stare::nameof_enum_entry<static_cast<E>(
                Is + static_cast<Int>(Min))>()...};
    };

    static constexpr auto all_entries =
        obtain_names<min>(std::make_integer_sequence<underlying_type, count>{});

    static constexpr std::size_t valid_entries_count = [] {
        std::size_t count = 0;

        for (std::string_view entry : all_entries)
        {
            if (stare::detail::is_enum_entry(entry))
            {
                ++count;
            }
        }

        return count;
    }();

    static constexpr std::array<E, valid_entries_count> entries_ = [] {
        auto                               enum_value = min;
        std::array<E, valid_entries_count> entries{};
        std::size_t                        arr_index = 0;

        for (std::string_view name : all_entries)
        {
            if (stare::detail::is_enum_entry(name))
            {
                entries[arr_index] = static_cast<E>(enum_value);
                ++arr_index;
            }

            ++enum_value;
        }

        return entries;
    }();

    template<std::size_t... Is>
    static constexpr auto
        tuple_entries_impl(std::index_sequence<Is...>) noexcept
    {
        return std::make_tuple(enum_entry<std::get<Is>(entries_)>{}...);
    }

    static constexpr auto tuple_entries =
        tuple_entries_impl(std::make_index_sequence<entries_.size()>{});

public:
    magic_enum_reflection() = default;

    static constexpr std::string_view name() noexcept
    {
        return stare::nameof_type<E>();
    }

    static constexpr const auto& entries() noexcept
    {
        return tuple_entries;
    }
}; // namespace stare

template<stare::enumeral E>
STARE_CONSTEVAL auto reflect_enum() noexcept
{
    return magic_enum_reflection<E>{};
}
} // namespace stare