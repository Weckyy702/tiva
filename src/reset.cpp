extern "C" {

volatile int x = 12;

void handle_reset() {
  x += 1;
  for (;;)
    ;
}
}
