#pragma once

#define _MAKE_INT(sign, n, original_type)                                      \
  using sign##n = original_type;                                               \
  constexpr auto operator""_##sign##n(unsigned long long int x) {              \
    return static_cast<original_type>(x);                                      \
  }                                                                            \
  static_assert(sizeof(original_type) * 8 == n)

#define MAKE_INT(n, original_type)                                             \
  _MAKE_INT(i, n, signed original_type);                                       \
  _MAKE_INT(u, n, unsigned original_type)

MAKE_INT(8, char);
MAKE_INT(16, short);
MAKE_INT(32, int);
MAKE_INT(64, long long int);

using isize = i32;
static_assert(sizeof(void *) == sizeof(isize));
constexpr auto operator""_isize(unsigned long long int x) {
  return static_cast<isize>(x);
}

using usize = u32;
static_assert(sizeof(void *) == sizeof(isize));
constexpr auto operator""_usize(unsigned long long int x) {
  return static_cast<usize>(x);
}
