#include <iostream>

#include "main.hpp"

sdl_container video{};

void toggleFullscreen()
{
  
  SDL_SetWindowFullscreen(video.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_Rect r;
  SDL_GetDisplayBounds(0, &r);
  SDL_Log("%d %d %d %d", r.x, r.y, r.w, r.h);
  SDL_SetWindowSize(video.window, r.w, r.h);
}


void cleanup()
{
  SDL_Log("Cleanup");
  if (video.mus)
  {
    Mix_HaltMusic();
    Mix_FreeMusic(video.mus);
  }

  Mix_CloseAudio();
  Mix_Quit();

  if (video.img)
  {
    SDL_DestroyTexture(video.img);
  }

  IMG_Quit();

  
  if (video.window)
  {
    SDL_DestroyWindow(video.window);
  }

  SDL_Quit();
}

void drawRect(Sint32 x, Sint32 y, int color)
{
  int _x = x * video.pixelRatio;
  int _y = y * video.pixelRatio;
  int _x2 = 100;
  int _y2 = 100;

  SDL_Rect r{
      _x, _y, _x2, _y2};

  
}

void drawRect(float x, float y, int color)
{
  int _x = x * video.sceneWidth * video.pixelRatio;
  int _y = y * video.sceneHeight * video.pixelRatio;
  int _x2 = 100;
  int _y2 = 100;

  SDL_Rect r{
      _x, _y, _x2, _y2};

  
}

void update()
{

  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    SDL_Log("* %x", event.type);
    switch (event.type)
    {
    case SDL_QUIT:
      video.running = false;
      break;
    case SDL_MOUSEMOTION:
    {
      SDL_MouseMotionEvent ev = event.motion;
      drawRect(ev.x, ev.y, 230);
      SDL_Log("mouse motion %d %d", ev.x, ev.y);
    }
    break;
    case SDL_FINGERMOTION:
    {
      SDL_TouchFingerEvent ev = event.tfinger;
      drawRect(ev.x, ev.y, 230);
      SDL_Log("finger motion %f %f", ev.x, ev.y);
    }
    break;
    case SDL_FINGERDOWN:
    {
      SDL_TouchFingerEvent ev = event.tfinger;
      drawRect(ev.x, ev.y, 230);
      Mix_PlayMusic(video.mus, 1);
      SDL_Log("finger down %f %f", ev.x, ev.y);
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
    {
      SDL_MouseButtonEvent ev = event.button;
      drawRect(ev.x, ev.y, 230);
      Mix_PlayMusic(video.mus, 1);
      SDL_Log("mouse down %d %d", ev.x, ev.y);
    }
    break;
    /*
    case SDL_MOUSEBUTTONUP:
    {
      SDL_MouseButtonEvent ev = event.button;
      SDL_Log("motion %d %d", ev.x, ev.y);
      drawRect(ev.x, ev.y, 230);
      Uint32 flags = SDL_GetWindowFlags(video.window);

      if (ev.x < video.sceneWidth / 4 && ev.y < video.sceneHeight / 4)
      {
        if (flags & SDL_WINDOW_FULLSCREEN)
        {
          SDL_SetWindowFullscreen(video.window, 0);
        }
        else
        {
          SDL_SetWindowFullscreen(video.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
      }
      else if (ev.x < video.sceneWidth / 4 && ev.y > 3 * video.sceneHeight / 4)
      {
        if (flags & SDL_WINDOW_FULLSCREEN)
        {
          SDL_SetWindowFullscreen(video.window, 0);
        }
        else
        {
          SDL_SetWindowFullscreen(video.window, SDL_WINDOW_FULLSCREEN);
        }
      }
      else if (ev.x > 3 * video.sceneWidth / 4 && ev.y > 3 * video.sceneHeight / 4)
      {
        incWindow();
      }
      else if (ev.x > 3 * video.sceneWidth / 4 && ev.y < video.sceneHeight / 4)
      {
        incSurface();
      }
    }
    break;*/
    case SDL_FINGERUP:
    {
      SDL_TouchFingerEvent ev = event.tfinger;
      drawRect(ev.x, ev.y, 230);
      Uint32 flags = SDL_GetWindowFlags(video.window);

      if (ev.x < 0.25f && ev.y < 0.25f)
      {
        if (flags & SDL_WINDOW_FULLSCREEN)
        {
          SDL_SetWindowFullscreen(video.window, 0);
          //SDL_RenderSetLogicalSize(video.renderer, 100,100);
          //SDL_RenderSetViewport(video.renderer, NULL);
        }
        else
        {
          SDL_SetWindowFullscreen(video.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
          SDL_Rect r{0,0,100,100};
          //SDL_RenderSetViewport(video.renderer, &r);
          //SDL_RenderSetLogicalSize(video.renderer, 0,0);
          
          
        }
      }
      else if (ev.x < 0.25f && ev.y > 0.75f)
      {
        if (flags & SDL_WINDOW_FULLSCREEN)
        {
          SDL_SetWindowFullscreen(video.window, 0);
          //SDL_RenderSetViewport(video.renderer, NULL);
        }
        else
        {
          
          SDL_SetWindowFullscreen(video.window, SDL_WINDOW_FULLSCREEN);
          SDL_Rect r{0,0,100,100};
          //SDL_RenderSetViewport(video.renderer, &r);
          //SDL_RenderSetLogicalSize(video.renderer, 0,0);
        }
      }
      else if (ev.x > 0.75f && ev.y > 0.75f)
      {
        incWindow();
      }
      else if (ev.x > 0.75f && ev.y < 0.25f)
      {
        incSurface();
      }
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
          // toggleFullscreen();
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
          SDL_Rect r;
          r.x = r.y = 0;
          r.w = ev.data1 * video.pixelRatio;
          r.h = ev.data2 * video.pixelRatio;
          video.sceneWidth = ev.data1;
          video.sceneHeight = ev.data2;
          SDL_Log("Resized to %d %d", ev.data1, ev.data2);

          logSize();
          // SDL_RenderSetViewport(video.renderer, &r);

          // emscripten_get_device_pixel_ratio()
          //.emscripten_get_screen_size(int *width, int *height)
          // emscripten_get_element_css_size(const char *target, double *width, double *height)
          // emscripten_get_canvas_element_size(const char *target, int *width, int *height)
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
  static float c = 0.f;
  if (c > 1.0f) {
    c = 0;
  }
  glClearColor(0.0f, c, 0.0f, 1.0f);
  c += 0.1f;
  
  glClear(GL_COLOR_BUFFER_BIT);
  //SDL_SetRenderDrawColor(video.renderer, 0, 0, 0, 255);
  //SDL_RenderClear(video.renderer);
  //SDL_RenderCopy(video.renderer, video.img, NULL, NULL);
}

void drawFrame()
{
  SDL_GL_SwapWindow(video.window);
  //SDL_RenderPresent(video.renderer);
}

void draw()
{
  //Uint32 start = SDL_GetTicks();
  startFrame();
  update();
  drawFrame();
  //SDL_Log("ms %d", SDL_GetTicks() - start);
}
