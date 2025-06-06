#include "snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

/* Fullscreen
 */
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1200

#define GRID_SIZE 20
#define GRID_DIMENSION 800

void render_grid(SDL_Renderer *renderer, int x, int y) {
  int cell_size = GRID_DIMENSION / GRID_SIZE;

  SDL_Rect cell;
  cell.w = cell_size;
  cell.w = cell_size;
  return;
}

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

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYUP:
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = true;
          break;
        }
      }
    }
    SDL_RenderClear(renderer);
    // RENDERLOOPSTR
    render_grid(renderer, 200, 200);
    // RENDERLOOPEND
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    SDL_ShowWindow(window);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
