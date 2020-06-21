#pragma once

#include <array>
#include <optional>
#include <string_view>

namespace stare
{
template<typename E>
concept enumeral = std::is_enum_v<E>;

namespace detail
{
template<typename T>
constexpr auto nameof_type_impl() noexcept
{
#if defined(__clang__)
    constexpr auto name = std::string_view{__PRETTY_FUNCTION__ + 44,
                                           sizeof(__PRETTY_FUNCTION__) - 46};
#elif defined(__GNUC__)
    constexpr auto name = std::string_view{__PRETTY_FUNCTION__ + 59,
                                           sizeof(__PRETTY_FUNCTION__) - 61};
    // TODO _MSC_VER
#else
    // make sure this only gets instantiated when the function is used
    constexpr auto name = std::string_view{};
    static_assert(!std::is_same_v<int, int>,
                  "stare::nameof_type: Unsupported compiler");
#endif

    return name;
}

template<auto val>
constexpr auto nameof_enum_entry_impl() noexcept
    requires(enumeral<decltype(val)>)
{
#if defined(__clang__)
    constexpr auto name = std::string_view{__PRETTY_FUNCTION__ + 52,
                                           sizeof(__PRETTY_FUNCTION__) - 54};
#elif defined(__GNUC__)
    constexpr auto name = std::string_view{__PRETTY_FUNCTION__ + 106,
                                           sizeof(__PRETTY_FUNCTION__) - 108};
#else
    constexpr auto name = std::string_view{};
    static_assert(!std::is_same_v<int, int>,
                  "stare::nameof_enum_entry: Unsupported compiler");
#endif
    return name;
}

constexpr bool is_digit(char c) noexcept
{
    return ('0' <= c) && (c <= '9');
}

constexpr bool is_enum_entry(std::string_view enum_str) noexcept
{
#if defined(__clang__)
    return !is_digit(enum_str[0]);
#elif defined(__GNUC__)
    return !enum_str.starts_with('(');
#else
    static_assert(!std::is_same_v<int, int>,
                  "stare::is_enum_entry: Unsupported compiler");
    return false;
#endif
}

template<class T>
struct nameof_helper
{
private:
    template<std::size_t... Is>
    static constexpr auto clean_name(std::index_sequence<Is...>,
                                     std::string_view dirty_name) noexcept
    {
        return std::array<char, sizeof...(Is) + 1>{dirty_name[Is]..., '\0'};
    }

public:
    static constexpr auto dirty_name = nameof_type_impl<T>();

    static constexpr auto cleaned_name =
        clean_name(std::make_index_sequence<dirty_name.size()>{}, dirty_name);
};

template<auto E>
requires stare::enumeral<decltype(E)> struct nameof_enum_entry_helper
{
private:
    template<std::size_t... Is>
    static constexpr auto clean_name(std::index_sequence<Is...>,
                                     std::string_view dirty_name) noexcept
    {
        return std::array<char, sizeof...(Is) + 1>{dirty_name[Is]..., '\0'};
    }

public:
    static constexpr auto dirty_name = nameof_enum_entry_impl<E>();

    static constexpr auto cleaned_name =
        clean_name(std::make_index_sequence<dirty_name.size()>{}, dirty_name);
};
} // namespace detail

// prefer auto return type in case return type changes
template<class T>
constexpr auto nameof_type() noexcept
{
    auto& cleaned_name = detail::nameof_helper<T>::cleaned_name;
    // remove one for trailing \0
    return std::string_view{cleaned_name.data(), cleaned_name.size() - 1};
}

template<auto E>
constexpr auto nameof_enum_entry() noexcept
    requires(stare::enumeral<decltype(E)>)
{
    auto& cleaned_name = detail::nameof_enum_entry_helper<E>::cleaned_name;
    return std::string_view{cleaned_name.data(), cleaned_name.size() - 1};
}

template<stare::enumeral E, std::underlying_type_t<E> I>
constexpr std::optional<std::string_view> try_nameof_enum_entry() noexcept
{
    // take the intermediate name to save on template instantiations
    constexpr auto name = detail::nameof_enum_entry_impl<static_cast<E>(I)>();
    if (stare::detail::is_enum_entry(name))
    {
        return std::optional{name};
    }
    else
    {
        return std::nullopt;
    }
}
} // namespace stare