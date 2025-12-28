#include <iostream>

#include "main.hpp"

sdl_container video{};

void toggleFullscreen()
{
  // SDL_SetWindowResizable(video.window, SDL_TRUE);
  SDL_SetWindowFullscreen(video.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_Rect r;
  SDL_GetDisplayBounds(0, &r);
  SDL_Log("%d %d %d %d", r.x, r.y, r.w, r.h);
  SDL_SetWindowSize(video.window, r.w, r.h);
}

void init()
{

  if (SDL_Init(SDL_INIT_VIDEO))
  {
    return;
  }

 
  SDL_Rect r;
  SDL_GetDisplayBounds(0, &r);
  SDL_Log(" init box %d %d %d %d", r.x, r.y, r.w, r.h);
  //SDL_SetWindowSize(video.window, r.w, r.h);
 
  video.window = SDL_CreateWindow(
    "Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, r.w, r.h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE
  );
  
  video.sceneWidth = r.w;
  video.sceneHeight = r.h;


  if (!video.window)
  {
    return;
  }

  video.renderer = SDL_CreateRenderer(
      video.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!video.renderer)
  {
    return;
  }

  
  SDL_RenderSetLogicalSize(video.renderer, 200,200);
  

  SDL_RendererInfo rendererInfo;
  SDL_GetRendererInfo(video.renderer, &rendererInfo);
  SDL_version ver;
  SDL_GetVersion(&ver);
  SDL_Log("Version %d %d %d",ver.major, ver.minor, ver.patch );
  SDL_Log("Revision %s", SDL_GetRevision());
  SDL_Log("Renderer: %s", rendererInfo.name);

  video.pixelRatio = 1.0f;
  video.running = true;

  IMG_Init(IMG_INIT_PNG);
  video.img = IMG_LoadTexture(video.renderer, "assets/Image5.png");
}

void cleanup()
{
  SDL_DestroyTexture(video.img);
  IMG_Quit();
  SDL_DestroyRenderer(video.renderer);
  SDL_DestroyWindow(video.window);
  SDL_Quit();
}

void drawRect(float x, float y, int color)
{
  int _x = x * video.sceneWidth * video.pixelRatio;
  int _y = y * video.sceneHeight * video.pixelRatio;
  int _x2 = 100;
  int _y2 = 100;

  SDL_Rect r{
      _x, _y, _x2, _y2};

  SDL_SetRenderDrawColor(video.renderer, 200, 0, color, 255);
  SDL_RenderFillRect(video.renderer, &r);
}

void update()
{

  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      video.running = false;
      break;
    case SDL_FINGERMOTION:
    {
      SDL_TouchFingerEvent ev = event.tfinger;
      drawRect(ev.x, ev.y, 230);
    }
    break;
    case SDL_FINGERDOWN:
    {
      SDL_TouchFingerEvent ev = event.tfinger;
      drawRect(ev.x, ev.y, 230);
    }
    break;
    case SDL_FINGERUP:
    {
      SDL_TouchFingerEvent ev = event.tfinger;
      drawRect(ev.x, ev.y, 230);
      // SDL_SetWindowFullscreen(video.window, true);
    }
    break;
    case SDL_SYSWMEVENT:
    {
      SDL_SysWMEvent ev = event.syswm;
      SDL_Log("SDL_SYSWMEVENT");
    }
    break;
    case SDL_DISPLAYEVENT:
    {
      SDL_DisplayEvent ev = event.display;
      switch (ev.event)
      {
      case SDL_DISPLAYEVENT_NONE:
        SDL_Log("SDL_DISPLAYEVENT_NONE");
        break;
      case SDL_DISPLAYEVENT_ORIENTATION:
        SDL_Log("SDL_DISPLAYEVENT_ORIENTATION");
        break;
      case SDL_DISPLAYEVENT_CONNECTED:
        SDL_Log("SDL_DISPLAYEVENT_CONNECTED");
        break;
      case SDL_DISPLAYEVENT_DISCONNECTED:
        SDL_Log("SDL_DISPLAYEVENT_DISCONNECTED");
        break;
      case SDL_DISPLAYEVENT_MOVED:
        SDL_Log("SDL_DISPLAYEVENT_MOVED");
        break;
      }
    }
    break;
    case SDL_WINDOWEVENT:
    {
      SDL_WindowEvent ev = event.window;
      switch (ev.event)
      {
      case SDL_WINDOWEVENT_NONE:
        SDL_Log("SDL_WINDOWEVENT_NONE");
        break;
      case SDL_WINDOWEVENT_SHOWN:
        SDL_Log("SDL_WINDOWEVENT_SHOWN");
        {
          toggleFullscreen();
          /*SDL_SetWindowResizable(video.window, true);
          SDL_Rect r;
          SDL_GetDisplayBounds(0, &r);
          SDL_Log("%d %d %d %d", r.x, r.y, r.w, r.h);
          SDL_SetWindowSize(video.window, r.w, r.h);*/
        }
        break;
      case SDL_WINDOWEVENT_HIDDEN:
        SDL_Log("SDL_WINDOWEVENT_HIDDEN");
        break;
      case SDL_WINDOWEVENT_EXPOSED:
        SDL_Log("SDL_WINDOWEVENT_EXPOSED");
        break;
      case SDL_WINDOWEVENT_MOVED:
        SDL_Log("SDL_WINDOWEVENT_MOVED");
        break;
      case SDL_WINDOWEVENT_RESIZED:
        SDL_Log("SDL_WINDOWEVENT_RESIZED");
        {
          video.sceneWidth = ev.data1;
          video.sceneHeight = ev.data2;
          char msg[40];
          sprintf(msg, "%d %d", ev.data1, ev.data2);
          SDL_Log("%s", msg);
        }
        break;
      case SDL_WINDOWEVENT_SIZE_CHANGED:
        SDL_Log("SDL_WINDOWEVENT_SIZE_CHANGED");
        {
          char msg[40];
          sprintf(msg, "%d %d", ev.data1, ev.data2);
          SDL_Log("%s", msg);
        }
        break;
      case SDL_WINDOWEVENT_MINIMIZED:
        SDL_Log("SDL_WINDOWEVENT_MINIMIZED");
        break;
      case SDL_WINDOWEVENT_MAXIMIZED:
        SDL_Log("SDL_WINDOWEVENT_MAXIMIZED");
        break;
      case SDL_WINDOWEVENT_RESTORED:
        SDL_Log("SDL_WINDOWEVENT_RESTORED");
        break;
      case SDL_WINDOWEVENT_ENTER:
        SDL_Log("SDL_WINDOWEVENT_ENTER");
        break;
      case SDL_WINDOWEVENT_LEAVE:
        SDL_Log("SDL_WINDOWEVENT_LEAVE");
        break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:
        SDL_Log("SDL_WINDOWEVENT_FOCUS_GAINED");
        break;
      case SDL_WINDOWEVENT_FOCUS_LOST:
        SDL_Log("SDL_WINDOWEVENT_FOCUS_LOST");
        break;
      case SDL_WINDOWEVENT_CLOSE:
        SDL_Log("SDL_WINDOWEVENT_CLOSE");
        break;
      case SDL_WINDOWEVENT_TAKE_FOCUS:
        SDL_Log("SDL_WINDOWEVENT_TAKE_FOCUS");
        break;
      case SDL_WINDOWEVENT_HIT_TEST:
        SDL_Log("SDL_WINDOWEVENT_HIT_TEST");
        break;
      case SDL_WINDOWEVENT_ICCPROF_CHANGED:
        SDL_Log("SDL_WINDOWEVENT_ICCPROF_CHANGED");
        break;
      case SDL_WINDOWEVENT_DISPLAY_CHANGED:
        SDL_Log("SDL_WINDOWEVENT_DISPLAY_CHANGED");
        break;
      default:
        break;
      }
    }
    break;
    default:
      break;
    }
  }
}

void startFrame()
{
  SDL_SetRenderDrawColor(video.renderer, 0, 0, 0, 255);
  SDL_RenderClear(video.renderer);
  SDL_RenderCopy(video.renderer, video.img, NULL, NULL);
}

void drawFrame()
{
  SDL_RenderPresent(video.renderer);
}

void draw()
{
  startFrame();
  update();
  drawFrame();
}
