#pragma once

#include "core/ints.hpp"

template <typename T = u32> struct Register {
  constexpr explicit Register(usize addr)
      : ptr_{reinterpret_cast<T volatile *>(addr)} {}

  constexpr T volatile &operator*() const { return ref(); }

  constexpr T volatile &ref() const { return *ptr_; }

private:
  T volatile *ptr_;
};
