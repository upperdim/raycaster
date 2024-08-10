#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "cli.h"
#include "map.h"
#include "util.h"
#include "game.h"
#include "debug.h"
#include "player.h"
#include "graphics.h"
#include "controls.h"

int init(SDL_Window **window, SDL_Surface **surface, Screen *scr)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	*window = SDL_CreateWindow("Ray Caster",
							   SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED,
							   640, 480,
							   SDL_WINDOW_RESIZABLE);
	if (!(*window)) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	*surface = SDL_GetWindowSurface(*window);
	if (!(*surface)) {
		printf("Error creating surface: %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	scr->pixelsArr = (*surface)->pixels;
	scr->width     = (*surface)->w;
	scr->height    = (*surface)->h;
	scr->format    = (*surface)->format;

	return 0;
}

int main(int argc, char *argv[])
{
	handle_args(&argc, argv);

	SDL_Window *window = NULL;
	SDL_Surface *windowSurface = NULL;
	Screen screen = {0};

	if (init(&window, &windowSurface, &screen)) {
		printf("Error! Failed to initialize.\n");
		return EXIT_FAILURE;
	}

	Player player = {14.7, 5.09, 0.0, 0.01, 0.0021};
	Keys   keys = {0};
	Map    map = map_import("maps/default.txt");

	clock_t oldtime = clock();
	while (!gameOver) {
		double delta = dt_ms(oldtime);
		oldtime = clock();

		handle_SDL_events(&screen, windowSurface, window, &keys);
		move_player(&player, &keys, &map, delta);

		screen_clear(&screen);
		render(&screen, &player, &map);

		SDL_UpdateWindowSurface(window);
		cap_framerate(delta);

		print_debug_info(&player, delta);
	}

	if (debugMode && debugOutOfScreenFlag) {
		printf("Warning: Out of screen occurred!\n");
	}

	SDL_FreeSurface(windowSurface);
	windowSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return 0;
}
