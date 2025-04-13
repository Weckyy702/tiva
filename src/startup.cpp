extern "C" {
[[gnu::used]] [[noreturn]] void _start() {
  float crash = 3.1415;
  for (;;)
    ;
}
}
