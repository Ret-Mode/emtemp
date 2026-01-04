#ifndef __TEMP_MAIN_HPP
#define __TEMP_MAIN_HPP

//#include "pch.hpp"

struct sdl_container
{
  SDL_Window *window;
  SDL_GLContext context;
  SDL_Texture *backbuffer;
  SDL_Surface *img;
  TTF_Font *font;
  Mix_Music *mus;
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
void logSize();
void incWindow();
void incSurface();

#endif //__TEMP_MAIN_HPP