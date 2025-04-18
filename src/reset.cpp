#include "irqs.hpp"

extern "C" {

[[gnu::target("thumb")]] void handle_reset() {

  ///
  /// PF1 = Red
  /// PF2 = Blue
  /// PF3 = Green

  for (;;)
    ;
}
}
