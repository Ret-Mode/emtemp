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

void logSize() {
  int iw, ih;
  double dw, dh;
  SDL_Rect r;
  SDL_RenderGetViewport(video.renderer, &r);
  SDL_Log( "Renderer viewpprt to %d %d %d %d", r.x, r.y, r.w, r.h);
  int w, h;
  SDL_GetRendererOutputSize(video.renderer, &w, &h);
  SDL_Log("pixel ratio %f", emscripten_get_device_pixel_ratio());
  SDL_Log("Rend output %d %d", w, h);
          
  SDL_GetWindowSize(video.window, &w, &h);
  SDL_Log("Wind output %d %d", w, h);
          
  SDL_GetWindowSizeInPixels(video.window, &w, &h);
  SDL_Log("Wind pixels output %d %d", w, h);
  emscripten_get_screen_size(&iw, &ih);
  SDL_Log("em scr size %d %d", iw, ih);
  emscripten_get_element_css_size("#canvas", &dw, &dh);
  SDL_Log("em css size %f %f", dw, dh);
  emscripten_get_canvas_element_size("#canvas", &iw, &ih);
  SDL_Log("em canvas size %d %d", iw, ih);
  Uint32 flags = SDL_GetWindowFlags(video.window);
	if((flags & SDL_WINDOW_FULLSCREEN) && (ih > iw)){
	  //SDL_Log("Try to lock on landscape");
    //emscripten_lock_orientation(EMSCRIPTEN_ORIENTATION_LANDSCAPE_PRIMARY);
	}
}

void incWindow() {
  double dw, dh;
  emscripten_get_element_css_size("#canvas", &dw, &dh);
  emscripten_set_element_css_size("#canvas", dw+10, dh+10);
}

void incSurface() {
  int iw, ih;
  emscripten_get_canvas_element_size("#canvas", &iw, &ih);
  emscripten_set_canvas_element_size("#canvas", iw + 10, ih +10);
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
  SDL_Log ("Entering main loop");
  emscripten_set_main_loop(mainloop, 0, true);
  return 0;
}