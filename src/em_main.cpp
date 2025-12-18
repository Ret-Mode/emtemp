#include <emscripten.h>
#include <emscripten/html5.h>

#include "main.hpp"

static void mainloop(void) {

  if (!video.running) {
    cleanup();
    emscripten_cancel_main_loop();

  }

  update();
  draw();

}

int main() {
  init();
  emscripten_set_main_loop(mainloop, 0, true);
  return 0;
}