#include "menu.h"
#include "highscore.h"
#include <string.h>
#include <stdio.h>

extern int screenWidth;
extern int screenHeight;
#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 70
#define numero_bot 4

void inicializar_botones(boton botones[]) {
    int startY = (screenHeight - (numero_bot * (BUTTON_HEIGHT + 20))) / 2;

    // Jugar
    botones[0].rect = (SDL_Rect){ (screenWidth - BUTTON_WIDTH)/2, startY, BUTTON_WIDTH, BUTTON_HEIGHT };
    botones[0].color = (SDL_Color){41,171,135,255};
    botones[0].hovercolor = (SDL_Color){63,224,176,255};
    botones[0].textcolor = (SDL_Color){255,255,255,255};
    strcpy(botones[0].label, "Jugar");
    botones[0].isHovered = false;

    // Ver puntaje
    botones[1].rect = (SDL_Rect){ (screenWidth - BUTTON_WIDTH)/2, startY + BUTTON_HEIGHT + 40, BUTTON_WIDTH, BUTTON_HEIGHT };
    botones[1].color = (SDL_Color){41,171,135,255};
    botones[1].hovercolor = (SDL_Color){63,224,176,255};
    botones[1].textcolor = (SDL_Color){255,255,255,255};
    strcpy(botones[1].label, "Ver puntaje");
    botones[1].isHovered = false;

    // Salir
    botones[2].rect = (SDL_Rect){ (screenWidth - BUTTON_WIDTH)/2, startY + 2*(BUTTON_HEIGHT + 40), BUTTON_WIDTH, BUTTON_HEIGHT };
    botones[2].color = (SDL_Color){220,20,60,255};
    botones[2].hovercolor = (SDL_Color){250,50,90,255};
    botones[2].textcolor = (SDL_Color){255,255,255,255};
    strcpy(botones[2].label, "Salir");
    botones[2].isHovered = false;
}

void inicializar_botones_dificultad(boton botones[]) {
    int num_dificultad = 3;
    int startY = (screenHeight - (num_dificultad * (BUTTON_HEIGHT + 20))) / 2;

    // Fácil
    botones[0].rect = (SDL_Rect){ (screenWidth - BUTTON_WIDTH)/2, startY, BUTTON_WIDTH, BUTTON_HEIGHT };
    botones[0].color = (SDL_Color){0,128,0,255};
    botones[0].hovercolor = (SDL_Color){50,205,50,255};
    botones[0].textcolor = (SDL_Color){255,255,255,255};
    strcpy(botones[0].label, "Nivel facil");
    botones[0].isHovered = false;

    // Medio
    botones[1].rect = (SDL_Rect){ (screenWidth - BUTTON_WIDTH)/2, startY + BUTTON_HEIGHT + 20, BUTTON_WIDTH, BUTTON_HEIGHT };
    botones[1].color = (SDL_Color){255,140,0,255};
    botones[1].hovercolor = (SDL_Color){255,200,120,255};
    botones[1].textcolor = (SDL_Color){255,255,255,255};
    strcpy(botones[1].label, "Nivel medio");
    botones[1].isHovered = false;

    // Difícil
    botones[2].rect = (SDL_Rect){ (screenWidth - BUTTON_WIDTH)/2, startY + 2*(BUTTON_HEIGHT + 20), BUTTON_WIDTH, BUTTON_HEIGHT };
    botones[2].color = (SDL_Color){220,20,60,255};
    botones[2].hovercolor = (SDL_Color){250,50,90,255};
    botones[2].textcolor = (SDL_Color){255,255,255,255};
    strcpy(botones[2].label, "Nivel dificil");
    botones[2].isHovered = false;
}

void render_botones(SDL_Renderer* renderer, boton botones[], int num_botones, TTF_Font* font) {
    for (int i = 0; i < num_botones; i++) {
        SDL_Color color = botones[i].isHovered ? botones[i].hovercolor : botones[i].color;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &botones[i].rect);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &botones[i].rect);

        SDL_Surface* textSurface = TTF_RenderText_Blended(font, botones[i].label, botones[i].textcolor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
            int textX = botones[i].rect.x + (botones[i].rect.w - textSurface->w) / 2;
            int textY = botones[i].rect.y + (botones[i].rect.h - textSurface->h) / 2;
            SDL_Rect textRect = {textX, textY, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

bool checkear(boton* boton, int mouseX, int mouseY) {
    return (mouseX >= boton->rect.x &&
            mouseX <= boton->rect.x + boton->rect.w &&
            mouseY >= boton->rect.y &&
            mouseY <= boton->rect.y + boton->rect.h);
}

int menu(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_SetWindowTitle(window, "Snek");

    //Tamaño para los botones
    TTF_Font* font = TTF_OpenFont("3270NerdFont-Regular.ttf", 40); 
    if (!font){
        printf("No se pudo cargar la fuente: %s, asegurese de tenerla instalada.\n", TTF_GetError());
        return -1;
    }

    //Tamaño para el título
    TTF_Font* font_titulo = TTF_OpenFont("3270NerdFont-Regular.ttf", 200); 
    if (!font_titulo){
        printf("No se pudo cargar la fuente para el título: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    boton botones[numero_bot];
    inicializar_botones(botones);

    bool running = true;
    SDL_Event event;
    int seleccion = -1; 

    while(running){
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEMOTION:
                    for (int i = 0; i < numero_bot; i++){
                        botones[i].isHovered = checkear(&botones[i], event.motion.x, event.motion.y);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        for (int i = 0; i < numero_bot; i++) {
                            if (checkear(&botones[i], event.button.x, event.button.y)) {
				    if (i == 1) {
					    mostrar_highscore_en_sdl(window);
				    } else {
					    seleccion = i;
					    running = false;
				    }	    
                            }
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        //Renderizar titulo
        SDL_Color tituloColor = {255, 255, 255, 255}; // Blanco
        SDL_Surface* tituloSurface = TTF_RenderText_Blended(font_titulo, "Snek", tituloColor);
        SDL_Texture* tituloTexture = SDL_CreateTextureFromSurface(renderer, tituloSurface);
        if (tituloTexture) {
            int tituloX = (screenWidth - tituloSurface->w) / 2;
            int tituloY = 40; 
            SDL_Rect tituloRect = {tituloX, tituloY, tituloSurface->w, tituloSurface->h};
            SDL_RenderCopy(renderer, tituloTexture, NULL, &tituloRect);
            SDL_DestroyTexture(tituloTexture);
        }
        SDL_FreeSurface(tituloSurface);

        
        render_botones(renderer, botones, numero_bot, font);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font_titulo);
    TTF_CloseFont(font);

    return seleccion; 
}

int menu_dificultad(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_SetWindowTitle(window, "Snek");
    //Tamaño para los botones
    TTF_Font* font = TTF_OpenFont("3270NerdFont-Regular.ttf", 40); 
    if (!font){
        printf("No se pudo cargar la fuente: %s, asegurese de tenerla instalada.\n", TTF_GetError());
        return -1;
    }

    //Tamaño para el título
    TTF_Font* font_titulo = TTF_OpenFont("3270NerdFont-Regular.ttf", 100); 
    if (!font_titulo){
        printf("No se pudo cargar la fuente para el título: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    boton botones[3];
    inicializar_botones_dificultad(botones);

    bool running = true;
    SDL_Event event;
    int seleccion = -1; 

    while(running){
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEMOTION:
                    for (int i = 0; i < 3; i++){
                        botones[i].isHovered = checkear(&botones[i], event.motion.x, event.motion.y);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        for (int i = 0; i < 3; i++) {
                            if (checkear(&botones[i], event.button.x, event.button.y)) {
                                seleccion = i;   
                                running = false; 
                            }
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        //Titulo en el menu de dificultad
        SDL_Color tituloColor = {255, 255, 255, 255}; // Blanco
        SDL_Surface* tituloSurface = TTF_RenderText_Blended(font_titulo, "Elije la dificultad", tituloColor);
        SDL_Texture* tituloTexture = SDL_CreateTextureFromSurface(renderer, tituloSurface);
        if (tituloTexture) {
            int tituloX = (screenWidth - tituloSurface->w) / 2;
            int tituloY = 40; 
            SDL_Rect tituloRect = {tituloX, tituloY, tituloSurface->w, tituloSurface->h};
            SDL_RenderCopy(renderer, tituloTexture, NULL, &tituloRect);
            SDL_DestroyTexture(tituloTexture);
        }
        SDL_FreeSurface(tituloSurface);

        render_botones(renderer, botones, 3, font);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);

    return seleccion; //Retorna 0, 1 o 2 según la dificultad elegida
}
