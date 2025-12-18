#ifndef __TEMP_MAIN_HPP
#define __TEMP_MAIN_HPP

#include <SDL2/SDL.h>

struct sdl_container {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *backbuffer;
  bool running;
};

extern sdl_container video;

void init();
void cleanup();
void update();
void draw();

#endif //__TEMP_MAIN_HPP