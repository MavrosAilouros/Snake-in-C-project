#include "score.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// Variable that holds our font

static TTF_Font* scoreFont = NULL;

// Function to initialize our font loader

void score_init(){
    if (TTF_Init() == -1 ) {
        printf("ERROR: failed to initialize TTF_init");
    }


    // Load font
    scoreFont = TTF_OpenFont("3270NerdFont-Regular.ttf", 20);
    if (!scoreFont) {
        printf("ERROR: Failed to load font");
    }
}

// Function to draw score

void score_draw (int current_score, SDL_Renderer *renderer) {

}

void score_cleanup() {

}
