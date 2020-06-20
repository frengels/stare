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
        .template field<T>("x", offsetof(vec3<T>, x), alignof(T), true)
        .template field<T>("y", offsetof(vec3<T>, y), alignof(T), true)
        .template field<T>("z", offsetof(vec3<T>, z), alignof(T), true)
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
            .template field<T>("x", offsetof(vec2<T>, x), alignof(T), true)
            .template field<T>("y", offsetof(vec2<T>, y), alignof(T), true)
            .build();
    }
};

TEST_CASE("struct")
{
    constexpr auto refl = stare::reflect<vec3<float>>();
    static_assert(std::get<0>(refl.fields()).offset == 0);
    static_assert(std::get<1>(refl.fields()).offset == 4);
}