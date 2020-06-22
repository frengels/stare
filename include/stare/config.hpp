#pragma once

#ifdef __cpp_consteval
#define STARE_CONSTEVAL consteval
#else
#define STARE_CONSTEVAL constexpr
#endif