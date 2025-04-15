#pragma once

#define _MAKE_INT(sign, n, original_type)                                      \
  using sign##n = original_type;                                               \
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
using usize = u32;
static_assert(sizeof(void *) == sizeof(isize));
