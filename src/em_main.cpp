#include <emscripten.h>
#include <emscripten/html5.h>

#include "main.hpp"

static void mainloop(void) {
  if (!video.running) {
    cleanup();
    emscripten_cancel_main_loop();
  }
  draw();
}

static void setPixelRatio(){
  video.pixelRatio = (float)emscripten_get_device_pixel_ratio();
  SDL_Log("%f pixel ratio", video.pixelRatio);
}

static void setOrientation() {
  //SDL_Rect r;
 // SDL_GetDisplayBounds(0, &r);
  //SDL_Log("%d %d %d %d", r.x, r.y, r.w, r.h);
  //SDL_SetWindowSize(video.window, r.w, r.h);
  //emscripten_request_fullscreen("#canvas", true);
  //emscripten_lock_orientation(EMSCRIPTEN_ORIENTATION_LANDSCAPE_PRIMARY);
}

int main() {
  init();
  SDL_Log("after init");
  setPixelRatio();
  setOrientation();
  SDL_Log ("Entering main loop");
  emscripten_set_main_loop(mainloop, 0, true);
  return 0;
}