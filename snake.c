#include "snake.h"
#include "score.h"
#include "menu.h"
#include "highscore.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>

// Fullscreen
//
#define WINDOW_X 0
#define WINDOW_Y 0
#define GRID_SIZE 20
#define GRID_DIMENSION 800

// Snake direction logic
//
enum {
  Snake_UP,
  Snake_DOWN,
  Snake_LEFT,
  Snake_RIGHT,
};

// type for game states

typedef enum {
  state_menu,
  state_facil,
  state_medio,
  state_dificil,
  state_exit
} game_state;

game_state currentState = state_menu;


typedef struct snake Snake;

Snake *head;
Snake *tail;
Apple *apple = NULL;
int score = 0;
int screenWidth = 0;
int screenHeight = 0;

// Create snake on the grid
//

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


bool check_self_collision() {
  Snake *current = head->next;
  while (current != NULL) {
    if (head->x == current->x && head->y == current->y) {
      return true;
    }
    current = current->next;
  }
  return false;
}

bool check_wall_collision() {
  return (head->x < 0 || head->x >= GRID_SIZE || head->y < 0 ||
          head->y >= GRID_SIZE);
}

bool check_apple_collision() {
  return (head->x == apple->x && head->y == apple->y);
}

void grow_snake() {

  Snake *new_segment = malloc(sizeof(Snake));
  new_segment->x = tail->x;
  new_segment->y = tail->y;
  new_segment->dir = tail->dir;
  new_segment->next = NULL;
  tail->next = new_segment;
  tail = new_segment;
}

void create_apple() {

  if (!apple) {
    apple = malloc(sizeof(Apple));
  }


  bool apple_on_snake;

  do {
    apple->x = rand() % GRID_SIZE;
    apple->y = rand() % GRID_SIZE;


    apple_on_snake = false;

    Snake *current = head;
    while (current != NULL){
      if (apple ->x == current ->x && apple->y == current->y){

        apple_on_snake = true;
        break;
      }
      current = current->next;
    }
 }
 while(apple_on_snake == true);
}

int main() {

  srand(time(NULL));
  SDL_Window *window;
  SDL_Renderer *renderer;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL_INIT_VIDEO ERROR");
  }

  window =
      SDL_CreateWindow("Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (!window) {
    fprintf(stderr, "ERROR:!window");
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

  if (!renderer) {
    fprintf(stderr, "ERROR:!renderer");
  }

  int grid_x = (screenWidth / 2) - (GRID_DIMENSION / 2);
  int grid_y = (screenHeight / 2) - (GRID_DIMENSION / 2);

  // Load font

  score_init();

  // our snek size hehe
  //

  int cell_size = GRID_DIMENSION / GRID_SIZE;

  SDL_ShowWindow(window);

  // Add in our little buddy :)
  //

  create_snake();

  // Add our apple

  create_apple();

  // Implement a tick counter --
  // to make our movement appear --
  // constant
  //

  Uint32 last_move = SDL_GetTicks();
  Uint32 Snake_Speed = 150; // time counter is in MS

  bool quit = false;
  SDL_Event event;
  while (!quit) {
// logic for controls
    //
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYUP:
          break;
        case SDL_KEYDOWN:
          if (currentState == state_facil || currentState == state_medio || currentState == state_dificil) {
            switch (event.key.keysym.sym) {
              case SDLK_UP:
                if (head->dir != Snake_DOWN) { head->dir = Snake_UP; }
                break;
              case SDLK_DOWN:
                if (head->dir != Snake_UP) { head->dir = Snake_DOWN; }
                break;
              case SDLK_LEFT:
                if (head->dir != Snake_RIGHT) { head->dir = Snake_LEFT; }
                break;
              case SDLK_RIGHT:
                if (head->dir != Snake_LEFT) { head->dir = Snake_RIGHT; }
                break;
            }
          }
          // The ESCAPE key SHOULD work in any state to quit (not tested)
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            currentState = state_menu;
          }
          break;
      }
    }

    // clr screen
    SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);
    SDL_RenderClear(renderer);


    switch (currentState) {

      case state_menu: {
        int menu_result = menu(window, renderer);
        if (menu_result == 0){
          int dificultad = menu_dificultad(window, renderer);
          if (dificultad == 0) {
            currentState=state_facil;
            Snake_Speed = 170; // time counter is in MS
          } else if(dificultad == 1){
            currentState= state_medio;
            Snake_Speed = 110; // time counter is in MS
          } else if (dificultad == 2){
            currentState=state_dificil;
            Snake_Speed=85;
          }

          score = 0; //Para que cada vez que se cambie de dificultad se comience en cero

          create_snake();
          create_apple();
          last_move=SDL_GetTicks();
        } else if (menu_result == 1){
		mostrar_highscore_en_sdl(window);
        } else if (menu_result == 2){
          quit=true;
          currentState = state_exit;
        }
        break; // End the menu case
      }

      case state_facil:{
        // base game logic
        Uint32 current_time = SDL_GetTicks();
        
        if (current_time - last_move > Snake_Speed) {
          Snake *new_head = (Snake *)malloc(sizeof(Snake));
          if (!new_head) { exit(1); }

          new_head->x = head->x;
          new_head->y = head->y;
          new_head->dir = head->dir;

          switch (new_head->dir) {
            case Snake_UP: new_head->y--; break;
            case Snake_DOWN: new_head->y++; break;
            case Snake_LEFT: new_head->x--; break;
            case Snake_RIGHT: new_head->x++; break;
          }

          new_head->next = head;
          head = new_head;

          if (check_apple_collision()) {
            create_apple();
            score += 1;
          } else {
            // tail logic
            if (head != tail) {
              Snake *current = head;
              while (current->next != tail) {
                current = current->next;
              }
              free(tail);
              tail = current;
              tail->next = NULL;
            } else {
              free(new_head->next);
              tail = new_head;
              tail->next = NULL;
            }
          }
          last_move = current_time;
        }

        if (check_wall_collision() || check_self_collision()) {
		int record = obtener_highscore();
		if (score > record) {
			guardar_highscore(score);
		}
          printf("Snek collided, game over :(\n");
          SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION,
            "Game Over :(",
            "Presiona OK para volver al menú.",
           window
            );
          currentState = state_menu;
        }

        // RENDERLOOPSTR
        render_grid(renderer, grid_x, grid_y);
        score_draw(score, renderer);

        // Initial render for snek
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 255);
        SDL_Rect snek_cell = {0,0,cell_size,cell_size}; // Initialize rect
        Snake *current_segment = head;
        while (current_segment) {
          snek_cell.x = grid_x + (current_segment->x * cell_size);
          snek_cell.y = grid_y + (current_segment->y * cell_size);
          SDL_RenderFillRect(renderer, &snek_cell);
          current_segment = current_segment->next;
        }

        // Render for apple
        if (apple != NULL) {
          SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 255);
          SDL_Rect apple_cell = {0,0,cell_size,cell_size}; // Initialize rect
          apple_cell.x = grid_x + (apple->x * cell_size);
          apple_cell.y = grid_y + (apple->y * cell_size);
          SDL_RenderFillRect(renderer, &apple_cell);
        }
        // RENDERLOOPEND

        break; // End the state_facil case
      }

        case state_medio:{
        // base game logic
        Uint32 current_time = SDL_GetTicks();
        
        if (current_time - last_move > Snake_Speed) {
          Snake *new_head = (Snake *)malloc(sizeof(Snake));
          if (!new_head) { exit(1); }

          new_head->x = head->x;
          new_head->y = head->y;
          new_head->dir = head->dir;

          switch (new_head->dir) {
            case Snake_UP: new_head->y--; break;
            case Snake_DOWN: new_head->y++; break;
            case Snake_LEFT: new_head->x--; break;
            case Snake_RIGHT: new_head->x++; break;
          }

          new_head->next = head;
          head = new_head;

          if (check_apple_collision()) {
            create_apple();
            score += 1;
          } else {
            // tail logic
            if (head != tail) {
              Snake *current = head;
              while (current->next != tail) {
                current = current->next;
              }
              free(tail);
              tail = current;
              tail->next = NULL;
            } else {
              free(new_head->next);
              tail = new_head;
              tail->next = NULL;
            }
          }
          last_move = current_time;
        }

        if (check_wall_collision() || check_self_collision()) {
		int record = obtener_highscore();
                if (score > record) {
                        guardar_highscore(score);
                }
          printf("Snek collided, game over :(\n");
          SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION,
            "Game Over :(",
            "Presiona OK para volver al menú.",
           window
            );
          currentState = state_menu;
        }

        // RENDERLOOPSTR
        render_grid(renderer, grid_x, grid_y);
        score_draw(score, renderer);

        // Initial render for snek
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 255);
        SDL_Rect snek_cell = {0,0,cell_size,cell_size}; // Initialize rect
        Snake *current_segment = head;
        while (current_segment) {
          snek_cell.x = grid_x + (current_segment->x * cell_size);
          snek_cell.y = grid_y + (current_segment->y * cell_size);
          SDL_RenderFillRect(renderer, &snek_cell);
          current_segment = current_segment->next;
        }

        // Render for apple
        if (apple != NULL) {
          SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 255);
          SDL_Rect apple_cell = {0,0,cell_size,cell_size}; // Initialize rect
          apple_cell.x = grid_x + (apple->x * cell_size);
          apple_cell.y = grid_y + (apple->y * cell_size);
          SDL_RenderFillRect(renderer, &apple_cell);
        }
        // RENDERLOOPEND

        break; // End the state_medio case
      }

        case state_dificil:{
        // base game logic
        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_move > Snake_Speed) {
          Snake *new_head = (Snake *)malloc(sizeof(Snake));
          if (!new_head) { exit(1); }

          new_head->x = head->x;
          new_head->y = head->y;
          new_head->dir = head->dir;

          switch (new_head->dir) {
            case Snake_UP: new_head->y--; break;
            case Snake_DOWN: new_head->y++; break;
            case Snake_LEFT: new_head->x--; break;
            case Snake_RIGHT: new_head->x++; break;
          }

          new_head->next = head;
          head = new_head;

          if (check_apple_collision()) {
            create_apple();
            score += 1;
          } else {
            // tail logic
            if (head != tail) {
              Snake *current = head;
              while (current->next != tail) {
                current = current->next;
              }
              free(tail);
              tail = current;
              tail->next = NULL;
            } else {
              free(new_head->next);
              tail = new_head;
              tail->next = NULL;
            }
          }
          last_move = current_time;
        }

        if (check_wall_collision() || check_self_collision()) {
		int record = obtener_highscore();
		if (score > record) {
			guardar_highscore(score);
		}
          printf("Snek collided, game over :(\n");
          SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION,
            "Game Over :(",
            "Presiona OK para volver al menú.",
           window
            );
           currentState = state_menu;
        }

        // RENDERLOOPSTR
        render_grid(renderer, grid_x, grid_y);
        score_draw(score, renderer);

        // Initial render for snek
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 255);
        SDL_Rect snek_cell = {0,0,cell_size,cell_size}; // Initialize rect
        Snake *current_segment = head;
        while (current_segment) {
          snek_cell.x = grid_x + (current_segment->x * cell_size);
          snek_cell.y = grid_y + (current_segment->y * cell_size);
          SDL_RenderFillRect(renderer, &snek_cell);
          current_segment = current_segment->next;
        }

        // Render for apple
        if (apple != NULL) {
          SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 255);
          SDL_Rect apple_cell = {0,0,cell_size,cell_size}; // Initialize rect
          apple_cell.x = grid_x + (apple->x * cell_size);
          apple_cell.y = grid_y + (apple->y * cell_size);
          SDL_RenderFillRect(renderer, &apple_cell);
        }
        // RENDERLOOPEND

        break; // End the state_dificil case
      }
        case state_exit:{
          quit = true;
        break;
        }
    
    }

    SDL_RenderPresent(renderer);
  }

  // clean functions
  score_cleanup();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
