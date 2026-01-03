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

void init()
{

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER))
  {
    cleanup();
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,0);
  
  SDL_Rect r;
  SDL_GetDisplayBounds(0, &r);

  video.window = SDL_CreateWindow(
      "Test",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      300, 200,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

  video.sceneWidth = r.w;
  video.sceneHeight = r.h;


  if (!video.window)
  {
    cleanup();
    return;
  }
  
  video.context = SDL_GL_CreateContext(video.window);
  if (!video.context){
    SDL_Log("no context");
    cleanup();
    return;
  }
  gladLoadGLES2Loader(SDL_GL_GetProcAddress);

  video.pixelRatio = 1.0f;

  if (IMG_Init(IMG_INIT_PNG) < 0)
  {
    SDL_Log("Png failed");
    cleanup();
    return;
  }

  //video.img = IMG_LoadTexture(video.renderer, "assets/Image5.png");

  if (Mix_Init(MIX_INIT_MOD) < 0)
  {
    SDL_Log("mod failed");
    cleanup();
    return;
  }
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096))
  {
    SDL_Log("audio device failed");
    cleanup();
    return;
  }

  video.mus = Mix_LoadMUS("assets/test.xm");
  video.running = true;
}

static void logDisplayMode(SDL_DisplayMode &dm) {
  SDL_Log("w %d h %d refresh %d", dm.w, dm.h, dm.refresh_rate);
}

void logSize() {
  int iw, ih;
  float ddpi, hdpi, vdpi;
  double dw, dh;
  float fw, fh;
  int w, h;
  SDL_Rect r;
  
  SDL_Log("pixel ratio %f", emscripten_get_device_pixel_ratio());
  
  SDL_GetDisplayDPI(0, &ddpi,  &hdpi, &vdpi);
  SDL_Log("Dpi d %f h %f v %f", ddpi, hdpi, vdpi);
  
  SDL_GetDisplayBounds(0, &r);
  SDL_Log( "Display bounds %d %d %d %d", r.x, r.y, r.w, r.h);
  
  SDL_GetWindowSize(video.window, &w, &h);
  SDL_Log("Wind output %d %d", w, h);
          
  SDL_GetWindowSizeInPixels(video.window, &w, &h);
  SDL_Log("Wind pixels output %d %d", w, h);
  
  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);
  SDL_Log("Desktop display");
  logDisplayMode(dm);
  
  SDL_GetCurrentDisplayMode(0, &dm);
  SDL_Log("Current display");
  logDisplayMode(dm);
  
  SDL_GetWindowDisplayMode(video.window, &dm);
  SDL_Log("Window display");
  logDisplayMode(dm);
  
  int modes = SDL_GetNumDisplayModes(0);
  for (int mode=0; mode < modes; ++mode){
    SDL_Log("Display ind %d", mode);
    SDL_GetDisplayMode(0, mode, &dm);
    logDisplayMode(dm);
  }
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


int main() {
  init();
  SDL_Log("after init");
  setPixelRatio();
  SDL_Log ("Entering main loop");
  emscripten_set_main_loop(mainloop, 0, true);
  return 0;
}