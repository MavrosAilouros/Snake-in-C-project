#include <stdio.h>
#include <SDL2/SDL.h>
#include "highscore.h"

#define HIGHSCORE_FILE "highscore.txt"

int obtener_highscore() {
	FILE *archivo = fopen(HIGHSCORE_FILE, "r");
	int highscore = 0;
	
	if (archivo == NULL) {
		return 0;
	}

	if (fscanf(archivo, "%d", &highscore) != 1) {
		highscore = 0;
	}

	fclose(archivo);
	return highscore;
}

void mostrar_highscore_en_sdl(SDL_Window *window) {
	int record = obtener_highscore();

	char mensaje[64];
	sprintf(mensaje, "Puntuacion mas alta; %d puntos", record);

	SDL_MessageBoxButtonData botones[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" }
	};

	SDL_MessageBoxData data = {
		SDL_MESSAGEBOX_INFORMATION,
		window,
		"Record",
		mensaje,
		SDL_arraysize(botones),
		botones,
		NULL
	};

	int boton_presionado;
	SDL_ShowMessageBox(&data, &boton_presionado);
}

void guardar_highscore(int score) {
	FILE *archivo = fopen(HIGHSCORE_FILE, "w");
	if (archivo != NULL) {
		fprintf(archivo, "%d", score);
		fclose(archivo);
	}
}