#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <SDL2/SDL.h>

int obtener_highscore(void);
void mostrar_highscore_en_sdl(SDL_Window *window);
void guardar_highscore(int score);

#endif