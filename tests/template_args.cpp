#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <vector>

#include <stare/template_arg.hpp>

TEST_CASE("template_args")
{
    SUBCASE("nttp")
    {
        auto tval = stare::nttp<std::size_t{50}>{};
        static_assert(tval.is_nttp());
        static_assert(!tval.is_type());
        static_assert(!tval.is_hkt());

        static_assert(tval.value() == 50);
    }

    SUBCASE("type")
    {
        auto ttype = stare::type<int>{};
        static_assert(ttype.is_type());
        static_assert(!ttype.is_nttp());
        static_assert(!ttype.is_hkt());
    }

    SUBCASE("hkt")
    {
        auto hkt = stare::hkt<std::vector>{};
        static_assert(hkt.is_hkt());
        static_assert(!hkt.is_nttp());
        static_assert(!hkt.is_type());
    }
}