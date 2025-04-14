#pragma once

template <typename T> struct MustInit {
  constexpr MustInit() = delete;

  constexpr explicit(false) MustInit(T const &v) : value{v} {}

  T value;
};
