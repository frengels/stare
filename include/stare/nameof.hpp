#pragma once

#include <array>
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
#elif defined(_MSC_VER)
#error "nameof_type not yet implemented for msvc"
#endif

    return name;
}

template<stare::enumeral E, E val>
constexpr auto nameof_enum_entry_impl() noexcept
{
#if defined(__clang__)
    constexpr auto name =
        std::string_view{__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__)};
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
} // namespace detail

// prefer auto return type in case return type changes
template<class T>
constexpr auto nameof_type() noexcept
{
    auto& cleaned_name = detail::nameof_helper<T>::cleaned_name;
    // remove one for trailing \0
    return std::string_view{cleaned_name.data(), cleaned_name.size() - 1};
}
} // namespace stare