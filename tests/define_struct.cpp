#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <stare/reflect.hpp>
#include <stare/reflection.hpp>
#include <stare/template_arg.hpp>

template<class T>
struct vec3
{
    [[no_unique_address]] T x;
    [[no_unique_address]] T y;
    [[no_unique_address]] T z;
};

template<typename T>
consteval auto reflect(std::in_place_type_t<vec3<T>>) noexcept
{
    return stare::make_reflection_for<vec3<T>>()
        .field(
            std::in_place_type<T>, "x", offsetof(vec3<T>, x), alignof(T), true)
        .field(
            std::in_place_type<T>, "y", offsetof(vec3<T>, y), alignof(T), true)
        .field(
            std::in_place_type<T>, "z", offsetof(vec3<T>, z), alignof(T), true)
        .build();
}

template<typename T>
struct vec2
{
    [[no_unique_address]] T x;
    [[no_unique_address]] T y;

    friend consteval auto reflect(std::in_place_type_t<vec2<T>>) noexcept
    {
        return stare::make_reflection_for<vec2<T>>()
            .field(std::in_place_type<T>,
                   "x",
                   offsetof(vec2<T>, x),
                   alignof(T),
                   true)
            .field(std::in_place_type<T>,
                   "y",
                   offsetof(vec2<T>, y),
                   alignof(T),
                   true)
            .build();
    }
};

struct color : vec3<uint8_t>
{
    friend consteval auto reflect(std::in_place_type_t<color>) noexcept
    {
        return stare::make_reflection_for<color>()
            .template base<vec3<uint8_t>>()
            .build();
    }
};

TEST_CASE("struct")
{
    SUBCASE("vec3")
    {
        using std::get;
        constexpr auto refl = stare::reflect<vec3<float>>();
        static_assert(get<0>(refl.fields()).offset() == 0);
        static_assert(get<1>(refl.fields()).offset() == 4);

        static_assert(refl.name() == "vec3<float>");
    }

    SUBCASE("vec4")
    {
        constexpr auto color_refl = stare::reflect<color>();

        static_assert(color_refl.name() == "color");
    }
}