#include <stdio.h>
#include "controls.h"
#include "debug.h"
#include "game.h"

void handle_SDL_events(Screen *screen, SDL_Surface *windowSurface, SDL_Window *window, Keys *keys)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameOver = true;
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				windowSurface = SDL_GetWindowSurface(window);
				screen->pixelsArr = windowSurface->pixels;
				screen->width = windowSurface->w;
				screen->height = windowSurface->h;
				if (debugMode) printf("Window resized to w: %d, h: %d\n", screen->width, screen->height);
			}
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				keys->up = 1;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				keys->down = 1;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				keys->left = 1;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				keys->right = 1;
				break;
			case SDL_SCANCODE_SPACE:
				keys->space = 1;
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
				keys->up = 0;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				keys->down = 0;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				keys->left = 0;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				keys->right = 0;
				break;
			case SDL_SCANCODE_SPACE:
				keys->space = 0;
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}
