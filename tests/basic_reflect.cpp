#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <stare/macros.hpp>
#include <stare/reflection.hpp>

template<class T>
struct type_
{
    using type = T;
};

namespace ns
{
struct my_base
{
    bool b;
};

struct my_other_base
{
    uint8_t u8;
};

template<class T>
struct my_type : my_base, my_other_base
{
    friend struct ::stare::reflection<my_type>;

    int   i;
    float f;
    T     t;
};
} // namespace ns

STARE_REFLECT(template(class T),
              type(ns::my_type<T>),
              inherits(ns::my_base, ns::my_other_base),
              fields(i, f, c, d));
// should expand to

/*
template<class T>
struct stare::reflection<ns::my_type<T>>
    : stare::reflection_interface<ns::my_type<T>>
{
    constexpr auto bases() const noexcept
    {
        return std::make_tuple(type_<ns::my_base>{});
    }

    constexpr auto fields() const noexcept
    {
        return std::make_tuple(stare::field<decltype(ns::my_type<T>::i)>(
                                   "i", offsetof(ns::my_type, i)),
                               stare::field<decltype(ns::my_type<T>::f)>(
                                   "f", offsetof(ns::my_type, f)),
                               stare::field<decltype(ns::my_type<T>::t)>(
                                   "t", offsetof(ns::my_type, t)));
    }
};
*/

template<class T>
class simple_type
{
    friend struct stare::reflection<simple_type<T>>;

private:
    int i;
    T   t;
};

STARE_REFLECT(template(class T), type(simple_type<T>), fields(i, t)
              /*, verify(true)*/);

TEST_CASE("basic_reflect")
{
    // check whether detecting reflections works
    static_assert(stare::reflected<ns::my_type<int>>);
    // check that int isn't reflected
    static_assert(!stare::reflected<int>);
    using my_reflect = stare::reflection<ns::my_type<int>>;

    constexpr auto simple_reflect = stare::reflection<simple_type<int>>{};
    constexpr auto field_i        = std::get<0>(simple_reflect.fields());
    static_assert(field_i.name == "i");
    static_assert(field_i.offset == 0);

    constexpr auto field_t = std::get<1>(simple_reflect.fields());
    static_assert(field_t.name == "t");
    static_assert(*field_t.offset == 4);
}
