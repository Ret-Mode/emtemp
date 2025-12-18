#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif
#include <SDL2/SDL.h>

void initialize_the_game() {}
void deinitialize_the_game() {}
void check_for_new_input() {}
void think_about_stuff() {}
void draw_the_next_frame() {}
bool game_is_still_running = true;

static void mainloop(void)   /* this will run often, possibly at the monitor's refresh rate */
{
  if (!game_is_still_running) {
    deinitialize_the_game();
  #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();  /* this should "kill" the app. */
  #else
    exit(0);
  #endif
  }

  check_for_new_input();
  think_about_stuff();
  draw_the_next_frame();
}

int main() {

  initialize_the_game();
  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(mainloop, 0, 1);
  #else
  while (1) { mainloop(); }
  #endif

return 0;
}