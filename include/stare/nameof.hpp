#pragma once

#include <array>
#include <string_view>

namespace stare
{
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
    return detail::nameof_helper<T>::cleaned_name;
}
} // namespace stare