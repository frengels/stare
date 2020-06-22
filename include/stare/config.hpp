#pragma once

#ifdef __cpp_consteval
#define STARE_CONSTEVAL consteval
#else
#define STARE_CONSTEVAL constexpr
#endif

#ifndef __clang__ // not in clang
#if defined(__GNUC__) && __GNUC__ < 10
#define STARE_GCC9_WORKAROUND
#endif
#endif