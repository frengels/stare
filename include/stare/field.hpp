#pragma once

#include <string_view>
#include <type_traits>

namespace stare
{
template<class Container, class T>
struct field
{
    using container_type = Container;

    /// type of the field
    using type = T;

    /// name of the field
    const std::string_view name;

    /// offset of this field within the class.
    /// offset is only available if the class has a standard layout, otherwise
    /// it's nullopt.
    const std::optional<std::size_t> offset;

    constexpr field(std::string_view           name,
                    std::optional<std::size_t> offset) noexcept
        : name(name), offset(offset)
    {}
};
} // namespace stare