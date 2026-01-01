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