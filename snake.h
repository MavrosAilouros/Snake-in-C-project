#ifndef SNAKE_H
#define SNAKE_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Graphics lib
 */
#include <SDL2/SDL.h>

// Estructura de cada parte de la serpiente
typedef struct snake {
    int x;
    int y;
    int dir;
    struct snake *next;
} Snake;

// Estructura de la manzana
typedef struct apple {
    int x;
    int y;
} Apple;

// Variables globales
extern Snake *head;
extern Snake *tail;
extern Apple *apple;

// Funciones para colisiones y juego

void create_apple();
bool check_self_collision();
bool check_wall_collision();
bool check_apple_collision();

#endif
