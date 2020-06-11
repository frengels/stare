#pragma once

#include <string_view>
#include <type_traits>

namespace stare
{
template<class T>
struct field
{
    using type = T;

    const std::string_view name;

    // offset only available if the class has a standard layout
    const std::optional<std::size_t> offset;

    constexpr field(std::string_view           name,
                    std::optional<std::size_t> offset) noexcept
        : name(name), offset(offset)
    {}
};
} // namespace stare