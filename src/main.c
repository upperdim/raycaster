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
		return 1;
	}

	*window = SDL_CreateWindow("Ray Caster",
							   SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED,
							   640, 480,
							   SDL_WINDOW_RESIZABLE);
	if (!(*window)) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	*surface = SDL_GetWindowSurface(*window);
	if (!(*surface)) {
		printf("Error creating surface: %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return 1;
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
		return 1;
	}

	Player player = {14.7, 5.09, 0.0, 0.01, 0.0021};
	Keys   keys = {0}; // despite looking sketchy, allows smooth movement w/ multiple keys
	Map    map = map_import("maps/default.txt");

	clock_t oldtime = clock();
	while (!gameOver) {
		double delta = dt_ms(oldtime);
		oldtime = clock();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				gameOver = true;
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					windowSurface = SDL_GetWindowSurface(window);
					screen.pixelsArr = windowSurface->pixels;
					screen.width = windowSurface->w;
					screen.height = windowSurface->h;
					if (debugMode) printf("Window resized to w: %d, h: %d\n", screen.width, screen.height);
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					keys.up = 1;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					keys.down = 1;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					keys.left = 1;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					keys.right = 1;
					break;
				case SDL_SCANCODE_Q:
				case SDL_SCANCODE_ESCAPE:
					gameOver = true;
					break;
				case SDL_SCANCODE_V:
					limitFramerate = !limitFramerate;
					if (debugMode) printf("Frame limiter switched to %s\n", limitFramerate ? "ON" : "OFF");
					break;
				default:
					break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					keys.up = 0;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					keys.down = 0;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					keys.left = 0;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					keys.right = 0;
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
		}

		if (keys.up && !keys.down) {
			double newposx = player.posx + sin(player.angle) * player.walkingspeed * delta;
			double newposy = player.posy + cos(player.angle) * player.walkingspeed * delta;

			if (!is_wall(map.data[(int) newposx * map.width + (int) newposy])) {
				player.posx = newposx;
				player.posy = newposy;
			}
		}

		if (keys.down && !keys.up) {
			double newposx = player.posx - sin(player.angle) * player.walkingspeed * delta;
			double newposy = player.posy - cos(player.angle) * player.walkingspeed * delta;

			if (!is_wall(map.data[(int) newposx * map.width + (int) newposy])) {
				player.posx = newposx;
				player.posy = newposy;
			}
		}

		if (keys.left && !keys.right) player.angle -= player.turningspeed * delta;
		if (keys.right && !keys.left) player.angle += player.turningspeed * delta;

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
