#ifndef __TEMP_MAIN_HPP
#define __TEMP_MAIN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct sdl_container {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *backbuffer;
  SDL_Texture *img;
  float pixelRatio;
  int sceneWidth;
  int sceneHeight;
  bool running;
};

extern sdl_container video;

void init();
void cleanup();
void update();
void draw();
void startFrame();
void drawFrame();

#endif //__TEMP_MAIN_HPP