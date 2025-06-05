#include "snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOWWIDTH 1000
#define WINDOWHEIGHT 1000

int main() {

  SDL_Window *window;
  SDL_Renderer *renderer;

  if (SDL_INIT_VIDEO < 0) {
    fprintf(stderr, "SDL_INIT_VIDEO ERROR");
  }

  window =
      SDL_CreateWindow("Snek", WINDOW_X, WINDOW_Y, WINDOWWIDTH, WINDOWHEIGHT,
                       SDL_WINDOW_BORDERLESS | SDL_WINDOW_HIDDEN);

  if (!window) {
    fprintf(stderr, "ERROR:!window");
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    fprintf(stderr, "ERROR:!renderer");
  }

  SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
  SDL_RenderClear(renderer);

  SDL_ShowWindow(window);
  SDL_RenderPresent(renderer);

  SDL_Delay(2000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
