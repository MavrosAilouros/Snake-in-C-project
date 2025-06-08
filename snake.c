#include "snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/* Fullscreen */
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1200

#define GRID_SIZE 20
#define GRID_DIMENSION 1000

/* Snake direction logic */
enum {
  Snake_UP,
  Snake_DOWN,
  Snake_LEFT,
  Snake_Right,
};

/* snake body parts*/

struct snake {
  int x;
  int y;
  int dir;
  struct snake *next;
};
typedef struct snake Snake;

Snake *head;
Snake *tail;

/*Create snake on the grid */

void create_snake() {

  Snake *new = malloc(sizeof(Snake));
  new->x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
  new->y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
  new->dir = Snake_UP;
  new->next = NULL;

  head = new;
  tail = new;

  return;
}

void grow_snake();

void render_grid(SDL_Renderer *renderer, int x, int y) {

  SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

  int cell_size = GRID_DIMENSION / GRID_SIZE;

  SDL_Rect cell;
  cell.w = cell_size;
  cell.h = cell_size;

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      cell.x = x + (i * cell_size);
      cell.y = y + (j * cell_size);
      SDL_RenderDrawRect(renderer, &cell);
    }
  }
  return;
}

// Function to handle snake movement
//

void snake_move() {

  // Snake Head logic
  //
  Snake *new_head = (Snake *)malloc(sizeof(Snake));
  if (!new_head) {
    fprintf(stderr, "ERROR:!new_head");
    exit(1);
  }

  new_head->x = head->x;
  new_head->y = head->y;
  new_head->dir = head->dir;
  new_head->next = head;

  head = new_head;

  // tail logic
  //

  if (head != tail) {

    Snake *current = head;
    while (current->next != tail) {
      current = current->next;
    }

    free(tail);

    tail = current;
    tail->next = NULL;
  }

  else {
    free(new_head->next);
    tail = new_head;
    tail->next = NULL;
  }
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

  int grid_x = (WINDOWWIDTH / 2) - (GRID_DIMENSION / 2);
  int grid_y = (WINDOWHEIGHT / 2) - (GRID_DIMENSION / 2);

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

    render_grid(renderer, grid_x, grid_y);

    // RENDERLOOPEND
    SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);
    SDL_ShowWindow(window);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
