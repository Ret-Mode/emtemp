#include <iostream>
#include <SDL2/SDL.h>

#include "main.hpp"


sdl_container video {};


void init() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    return;
  }

  video.window = SDL_CreateWindow(
    "Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );

  if (!video.window) {
    return;
  }

  video.renderer = SDL_CreateRenderer(
    video.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (!video.renderer) {
    return;
  }
  video.running = true;
}


void cleanup() {
  SDL_DestroyRenderer(video.renderer);
	SDL_DestroyWindow(video.window);
  SDL_Quit();
}


void update() {
  
  SDL_Event event;

  while (SDL_PollEvent(&event))
	{
    switch (event.type) {
      case SDL_QUIT:
      video.running = false;
      break;
    }

	}
}


void draw() {

  static int i{0};

  SDL_SetRenderDrawColor( video.renderer, 0, 0, 0, 255 );
  SDL_RenderClear( video.renderer );

  SDL_Rect r{50,50,50,50};

  SDL_SetRenderDrawColor( video.renderer, 0, 0, i++, 255 );
  SDL_RenderFillRect( video.renderer, &r );
  SDL_RenderPresent(video.renderer);
	
}
