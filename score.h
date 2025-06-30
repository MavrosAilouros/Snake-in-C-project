#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>

// function to load the font

void score_init(void);

//function to draw score on the screen

void score_draw(int current_score, SDL_Renderer *renderer);

//function to clear the font

void score_cleanup(void);

#endif
