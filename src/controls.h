#ifndef __CONTROLS_H_
#define __CONTROLS_H_

#include <SDL2/SDL.h>
#include "graphics.h"

typedef struct Keys {
	int up;
	int down;
	int left;
	int right;
} Keys;

void handle_SDL_events(Screen *screen, SDL_Surface *windowSurface, SDL_Window *window, Keys *keys);

#endif