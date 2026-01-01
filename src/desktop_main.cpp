#include "main.hpp"

static void mainloop(void) {
  if (!video.running) {
    cleanup();
    exit(0);
  }
  draw();
}

void logSize(){
  
}

int main() {
  init();
  while (1) { mainloop(); }
  return 0;
}