#include "irqs.hpp"

#define MAKE_BLOCKING_HANDLER(name)                                            \
  extern "C" [[gnu::weak]] void handle_##name(void) {                          \
    for (;;) {                                                                 \
    }                                                                          \
  }

FOR_EACH_SYSEXCEPT(MAKE_BLOCKING_HANDLER)

[[gnu::weak]] void thing();
