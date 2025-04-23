#include "core/Register.hpp"
#include "core/ints.hpp"
#include "irqs.hpp"

extern "C" void handle_reset() {

  /// PF1 = Red
  /// PF2 = Blue
  /// PF3 = Green

  constexpr auto GPIOFBASE = 0x4002'5000_usize;

  auto const RCGCGPIO = Register(0x400F'E608);
  auto const GPIOFDIR = Register(GPIOFBASE + 0x400);
  auto const GPIOFDEN = Register(GPIOFBASE + 0x51C);
  // The address encodes a bitmask
  auto const GPIOFDATA = Register(GPIOFBASE + (0xff << 2u));

  // Enable clocking to the GPIOF peripheral
  *RCGCGPIO |= 1u << 5;

  // Set PF1/2/3 to output
  *GPIOFDIR |= 0b1110;
  // Enable digital output for PF1/2/3
  *GPIOFDEN |= 0b1110;
  // Enable
  *GPIOFDATA = 0xff;

  for (;;)
    ;
}
