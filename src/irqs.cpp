#include "irqs.hpp"

extern "C" void blocking_handler(void) {
  for (;;)
    ;
}

extern "C" void null_handler(void) {}

#define MAKE_WEAK_BLOCKING_HANDLER(name)                                       \
  [[gnu::weak, gnu::alias("blocking_handler")]] void handle_##name(void);

FOR_EACH_SYSEXCEPT(MAKE_WEAK_BLOCKING_HANDLER)

#define MAKE_WEAK_NULL_HANDLER(name, _)                                        \
  [[gnu::weak, gnu::alias("null_handler")]] void handle_##name(void);

FOR_EACH_IRQ(MAKE_WEAK_NULL_HANDLER)
