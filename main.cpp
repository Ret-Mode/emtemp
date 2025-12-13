#include <iostream>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
bool one_iter(double time, void* userData) {
  return true;
}

int main() {
#ifdef __EMSCRIPTEN__
  // Receives a function to call and some user data to provide it.
  emscripten_request_animation_frame_loop(one_iter, 0);
#else
  while (1) {
    one_iter();
    // Delay to keep frame rate constant (using SDL).
    SDL_Delay(1);
  }
#endif
return 0;
}