#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hovercolor;
    SDL_Color textcolor;
    char label[20];
    bool isHovered;
} boton;

// Inicializa los botones del menú principal
void inicializar_botones(boton botones[]);

// Inicializa los botones del submenú de dificultad
void inicializar_botones_dificultad(boton botones[]);

// Renderiza los botones
void render_botones(SDL_Renderer* renderer, boton botones[], int num_botones, TTF_Font* font);

// Verifica si el mouse está sobre el botón
bool checkear(boton* boton, int mouseX, int mouseY);

// Menú principal
int menu(SDL_Window* window, SDL_Renderer* renderer);

// Submenú de dificultad
int menu_dificultad(SDL_Window* window, SDL_Renderer* renderer);

#endif