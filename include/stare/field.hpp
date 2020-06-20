#pragma once

#include <cassert>
#include <cstring>
#include <span>
#include <string_view>
#include <type_traits>

namespace stare
{
template<class Container, class T>
struct field
{
    using class_type = Container;

    /// type of the field
    using value_type = T;

    /// name of the field
    std::string_view name;

    /// offset of this field within the class.
    std::size_t offset;
    std::size_t align;
    bool        no_unique_address;

    constexpr field(std::in_place_type_t<Container>,
                    std::in_place_type_t<T>,
                    std::string_view name,
                    std::size_t      offset,
                    std::size_t      align             = alignof(T),
                    bool             no_unique_address = false) noexcept
        : field(name, offset, align, no_unique_address)
    {}

    constexpr field(std::string_view name,
                    std::size_t      offset,
                    std::size_t      align             = alignof(T),
                    bool             no_unique_address = false) noexcept
        : name(name), offset(offset), align(align),
          no_unique_address(no_unique_address)
    {}

    inline value_type& extract(class_type& cont) const noexcept
    {
        auto bytes = std::as_writable_bytes(
            std::span<class_type, 1>{std::addressof(cont), 1});

        auto*       type_byte = bytes.data() + offset;
        value_type* t_ptr;
        std::memcpy(&t_ptr, type_byte, sizeof(value_type*));

        return *t_ptr;
    }

    inline const value_type& extract_from(const class_type& inst) const noexcept
    {
        auto bytes = std::as_bytes(
            std::span<const class_type, 1>{std::addressof(inst), 1});
        auto field_first_byte = bytes.data() + offset;

        value_type* field_ptr;
        std::memcpy(&field_ptr, &field_first_byte, sizeof(value_type*));
        return *field_ptr;
    }
};
} // namespace stare