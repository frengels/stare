#pragma once

#include <optional>
#include <tuple>
#include <type_traits>

#include "stare/field.hpp"
#include "stare/reflection.hpp"

#define STARE_PP_PRIMITIVE_CAT(a, ...) a##__VA_ARGS__
#define STARE_PP_CAT(a, ...) STARE_PP_PRIMITIVE_CAT(a, __VA_ARGS__)

#define STARE_PP_EAT(...)
#define STARE_PP_EXPAND(...) __VA_ARGS__
#define STARE_PP_EMPTY()
#define STARE_PP_DEFER(Id) Id STARE_PP_EMPTY()

#define STARE_PP_FIELD(fieldname)                                              \
    ::stare::field<decltype(value_type::fieldname)>(                           \
        #fieldname,                                                            \
        std::is_standard_layout<value_type>::value ?                           \
            std::optional<std::size_t>(offsetof(value_type, fieldname)) :      \
            std::optional<std::size_t>())

#define STARE_PP_EX_(Specifier, ...) STARE_PP_EX_##Specifier __VA_ARGS__

#define STARE_PP_TEMPLATE(...) template<__VA_ARGS__>
#define STARE_PP_TYPE(x)                                                       \
    struct stare::reflection<x> : ::stare::detail::reflection_interface<x>     \
    {                                                                          \
        using value_type = x;

#define STARE_PP_INHERITS(...)                                                 \
    constexpr auto bases() const noexcept                                      \
    {                                                                          \
        return ::stare::type_list<__VA_ARGS__>{};                              \
    }

#define STARE_PP_END() }

#define STARE_PP_EX_template(...) STARE_PP_TEMPLATE(__VA_ARGS__)
#define STARE_PP_EX_type(x) STARE_PP_TYPE(x)
#define STARE_PP_EX_inherits(...) STARE_PP_INHERITS(__VA_ARGS__)
#define STARE_PP_EX_fields(...)                                                \
    constexpr auto fields() const noexcept                                     \
    {                                                                          \
        return ::std::make_tuple(                                              \
            STARE_PP_FOR_EACH_FIELD(STARE_PP_FIELD, __VA_ARGS__));             \
    }

#define STARE_REFLECT(...)                                                     \
    STARE_PP_FOR_EACH(STARE_PP_EX_, __VA_ARGS__)                               \
    STARE_PP_EXPAND(STARE_PP_DEFER(STARE_PP_END()))

#define STARE_PP_FOR_EACH_0(...)

#define STARE_PP_FOR_EACH_1(op, x, ...) op(x)
#define STARE_PP_FOR_EACH_2(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_1(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_3(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_2(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_4(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_3(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_5(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_4(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_6(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_5(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_7(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_6(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_8(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_7(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_9(op, x, ...)                                        \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_8(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_10(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_9(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_11(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_10(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_12(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_11(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_13(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_12(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_14(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_13(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_15(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_14(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_16(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_15(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_17(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_16(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_18(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_17(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_19(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_18(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_20(op, x, ...)                                       \
    op(x) STARE_PP_EXPAND(STARE_PP_FOR_EACH_19(op, __VA_ARGS__))

#define STARE_PP_FOR_EACH_NARG(...)                                            \
    STARE_PP_FOR_EACH_NARG_(__VA_ARGS__, STARE_PP_FOR_EACH_RSEQ_N())
#define STARE_PP_FOR_EACH_NARG_(...)                                           \
    STARE_PP_EXPAND(STARE_PP_FOR_EACH_ARG_N(__VA_ARGS__))
#define STARE_PP_FOR_EACH_ARG_N(_1,                                            \
                                _2,                                            \
                                _3,                                            \
                                _4,                                            \
                                _5,                                            \
                                _6,                                            \
                                _7,                                            \
                                _8,                                            \
                                _9,                                            \
                                _10,                                           \
                                _11,                                           \
                                _12,                                           \
                                _13,                                           \
                                _14,                                           \
                                _15,                                           \
                                _16,                                           \
                                _17,                                           \
                                _18,                                           \
                                _19,                                           \
                                _20,                                           \
                                _21,                                           \
                                _22,                                           \
                                _23,                                           \
                                _24,                                           \
                                _25,                                           \
                                _26,                                           \
                                _27,                                           \
                                _28,                                           \
                                _29,                                           \
                                _30,                                           \
                                _31,                                           \
                                _32,                                           \
                                _33,                                           \
                                _34,                                           \
                                _35,                                           \
                                _36,                                           \
                                _37,                                           \
                                _38,                                           \
                                _39,                                           \
                                _40,                                           \
                                _41,                                           \
                                _42,                                           \
                                _43,                                           \
                                _44,                                           \
                                _45,                                           \
                                _46,                                           \
                                _47,                                           \
                                _48,                                           \
                                _49,                                           \
                                _50,                                           \
                                _51,                                           \
                                _52,                                           \
                                _53,                                           \
                                _54,                                           \
                                _55,                                           \
                                _56,                                           \
                                _57,                                           \
                                _58,                                           \
                                _59,                                           \
                                _60,                                           \
                                _61,                                           \
                                _62,                                           \
                                _63,                                           \
                                _64,                                           \
                                _65,                                           \
                                _66,                                           \
                                _67,                                           \
                                _68,                                           \
                                _69,                                           \
                                _70,                                           \
                                _71,                                           \
                                _72,                                           \
                                _73,                                           \
                                _74,                                           \
                                _75,                                           \
                                _76,                                           \
                                _77,                                           \
                                _78,                                           \
                                _79,                                           \
                                _80,                                           \
                                _81,                                           \
                                _82,                                           \
                                _83,                                           \
                                _84,                                           \
                                _85,                                           \
                                _86,                                           \
                                _87,                                           \
                                _88,                                           \
                                _89,                                           \
                                _90,                                           \
                                _91,                                           \
                                _92,                                           \
                                _93,                                           \
                                _94,                                           \
                                _95,                                           \
                                _96,                                           \
                                _97,                                           \
                                _98,                                           \
                                _99,                                           \
                                _100,                                          \
                                _101,                                          \
                                _102,                                          \
                                _103,                                          \
                                _104,                                          \
                                _105,                                          \
                                _106,                                          \
                                _107,                                          \
                                _108,                                          \
                                _109,                                          \
                                _110,                                          \
                                _111,                                          \
                                _112,                                          \
                                _113,                                          \
                                _114,                                          \
                                _115,                                          \
                                _116,                                          \
                                _117,                                          \
                                _118,                                          \
                                _119,                                          \
                                _120,                                          \
                                _121,                                          \
                                _122,                                          \
                                _123,                                          \
                                _124,                                          \
                                _125,                                          \
                                _126,                                          \
                                _127,                                          \
                                _128,                                          \
                                N,                                             \
                                ...)                                           \
    N

// neovim: :put=range(128, 0, -1) then do a macro after that
#define STARE_PP_FOR_EACH_RSEQ_N()                                             \
    128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, \
        113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  \
        99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83,    \
        82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66,    \
        65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49,    \
        48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,    \
        31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,    \
        14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define STARE_PP_FOR_EACH_(N, op, ...)                                         \
    STARE_PP_EXPAND(                                                           \
        STARE_PP_PRIMITIVE_CAT(STARE_PP_FOR_EACH_, N)(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH(op, ...)                                             \
    STARE_PP_FOR_EACH_(STARE_PP_FOR_EACH_NARG(__VA_ARGS__), op, __VA_ARGS__)

#define STARE_PP_FOR_EACH_FIELD_0(...)
#define STARE_PP_FOR_EACH_FIELD_1(op, x, ...) op(x)
#define STARE_PP_FOR_EACH_FIELD_2(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_1(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_3(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_2(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_4(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_3(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_5(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_4(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_6(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_5(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_7(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_6(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_8(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_7(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_9(op, x, ...)                                  \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_8(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_10(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_9(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_11(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_10(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_12(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_11(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_13(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_12(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_14(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_13(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_15(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_14(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_16(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_15(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_17(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_16(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_18(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_17(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_19(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_18(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_20(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_19(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_21(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_20(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_22(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_21(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_23(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_22(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_24(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_23(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_25(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_24(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_26(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_25(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_27(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_26(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_28(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_27(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_29(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_28(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_30(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_29(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_31(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_30(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_32(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_31(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_33(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_32(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_34(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_33(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_35(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_34(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_36(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_35(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_37(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_36(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_38(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_37(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_39(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_38(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_40(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_39(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_41(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_40(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_42(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_41(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_43(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_42(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_44(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_43(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_45(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_44(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_46(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_45(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_47(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_46(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_48(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_47(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_49(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_48(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_50(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_49(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_51(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_50(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_52(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_51(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_53(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_52(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_54(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_53(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_55(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_54(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_56(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_55(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_57(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_56(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_58(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_57(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_59(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_58(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_60(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_59(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_61(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_60(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_62(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_61(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_63(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_62(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_64(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_63(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_65(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_64(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_66(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_65(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_67(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_66(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_68(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_67(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_69(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_68(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_70(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_69(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_71(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_70(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_72(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_71(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_73(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_72(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_74(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_73(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_75(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_74(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_76(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_75(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_77(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_76(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_78(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_77(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_79(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_78(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_80(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_79(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_81(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_80(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_82(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_81(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_83(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_82(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_84(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_83(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_85(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_84(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_86(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_85(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_87(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_86(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_88(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_87(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_89(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_88(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_90(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_89(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_91(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_90(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_92(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_91(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_93(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_92(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_94(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_93(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_95(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_94(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_96(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_95(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_97(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_96(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_98(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_97(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_99(op, x, ...)                                 \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_98(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_100(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_99(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_101(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_100(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_102(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_101(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_103(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_102(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_104(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_103(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_105(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_104(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_106(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_105(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_107(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_106(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_108(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_107(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_109(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_108(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_110(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_109(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_111(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_110(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_112(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_111(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_113(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_112(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_114(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_113(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_115(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_114(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_116(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_115(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_117(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_116(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_118(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_117(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_119(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_118(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_120(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_119(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_121(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_120(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_122(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_121(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_123(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_122(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_124(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_123(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_125(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_124(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_126(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_125(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_127(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_126(op, __VA_ARGS__))
#define STARE_PP_FOR_EACH_FIELD_128(op, x, ...)                                \
    op(x), STARE_PP_EXPAND(STARE_PP_FOR_EACH_FIELD_127(op, __VA_ARGS__))

#define STARE_PP_FOR_EACH_FIELD_(N, op, ...)                                   \
    STARE_PP_EXPAND(                                                           \
        STARE_PP_PRIMITIVE_CAT(STARE_PP_FOR_EACH_FIELD_, N)(op, __VA_ARGS__))

#define STARE_PP_FOR_EACH_FIELD(op, ...)                                       \
    STARE_PP_FOR_EACH_FIELD_(                                                  \
        STARE_PP_FOR_EACH_NARG(__VA_ARGS__), op, __VA_ARGS__)
