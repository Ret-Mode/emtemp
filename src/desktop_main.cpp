#include "main.hpp"

static void mainloop(void) {

  if (!video.running) {
    cleanup();
    exit(0);
  }

  update();
  draw();

}

int main() {
  init();
  while (1) { mainloop(); }
  return 0;
}