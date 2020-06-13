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
    using field_type = T;

    /// name of the field
    const std::string_view name;

    /// offset of this field within the class.
    const std::size_t offset;

    constexpr field(std::string_view name, std::size_t offset) noexcept
        : name(name), offset(offset)
    {}

    inline field_type& extract(class_type& cont) const noexcept
    {
        auto bytes = std::as_writable_bytes(
            std::span<class_type, 1>{std::addressof(cont), 1});

        auto*       type_byte = bytes.data() + offset;
        field_type* t_ptr;
        std::memcpy(&t_ptr, type_byte, sizeof(field_type*));

        return *t_ptr;
    }

    inline const field_type& extract_from(const class_type& inst) const noexcept
    {
        auto bytes = std::as_bytes(
            std::span<const class_type, 1>{std::addressof(inst), 1});
        auto field_first_byte = bytes.data() + offset;

        field_type* field_ptr;
        std::memcpy(&field_ptr, &field_first_byte, sizeof(field_type*));
        return *field_ptr;
    }
};
} // namespace stare