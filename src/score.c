#include "score.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// Variable that holds our font

static TTF_Font* score_font = NULL;

// Function to initialize our font loader

void score_init(){
    if (TTF_Init() == -1 ) {
        printf("ERROR: failed to initialize TTF_init");
    }


    // Load font
    score_font = TTF_OpenFont("3270NerdFont-Regular.ttf", 26);
    if (!score_font) {
        printf("ERROR: Failed to load font");
    }
}

// Function to draw score

void score_draw (int current_score, SDL_Renderer *renderer) {

    char score_text[100];

    snprintf(score_text, 100, "Score: %d", current_score);

    SDL_Color white = {255, 255, 255, 255};

    // Drawing parameters

    SDL_Surface* score_surface = TTF_RenderText_Solid(score_font, score_text, white);

    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

    SDL_Rect scoreRect;
    scoreRect.x = 10;
    scoreRect.y = 10;
    scoreRect.w = score_surface->w;
    scoreRect.h = score_surface->h;

    SDL_RenderCopy(renderer, score_texture, NULL, &scoreRect);
    SDL_FreeSurface(score_surface);
    SDL_DestroyTexture(score_texture);

}

// Function to free the font parameters

void score_cleanup() {

    TTF_CloseFont(score_font);
    TTF_Quit();

}
