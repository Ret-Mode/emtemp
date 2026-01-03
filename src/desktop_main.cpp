#include "main.hpp"

static void mainloop(void)
{
  if (!video.running)
  {
    cleanup();
    exit(0);
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

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
  
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
  gladLoadGLLoader(SDL_GL_GetProcAddress);

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

void logSize()
{
}

void incWindow()
{
}

void incSurface()
{
}

int main(int argv, char **argc)
{
  init();
  while (1)
  {
    mainloop();
  }
  return 0;
}