#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <stare/enum.hpp>

enum struct no_namespace
{
    entry1,
    entry2,
};

namespace myns
{
enum struct namespaced
{
    entry1,
    entry2,
};
}

TEST_CASE("enum")
{
    SUBCASE("nameof")
    {
        static_assert(stare::nameof_type<no_namespace>() == "no_namespace");
        static_assert(stare::nameof_type<myns::namespaced>() ==
                      "myns::namespaced");

        static_assert(stare::nameof_enum_entry<no_namespace::entry1>() ==
                      "no_namespace::entry1");
        static_assert(stare::nameof_enum_entry<myns::namespaced::entry1>() ==
                      "myns::namespaced::entry1");
    }

    SUBCASE("is_entry")
    {
        static_assert(
            !stare::try_nameof_enum_entry<no_namespace, 50>().has_value());
        static_assert(stare::try_nameof_enum_entry<no_namespace, 0>().value() ==
                      "no_namespace::entry1");
    }
}