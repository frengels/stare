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
    static_assert(stare::nameof_type<no_namespace>() == "no_namespace");
    static_assert(stare::nameof_type<myns::namespaced>() == "myns::namespaced");
}