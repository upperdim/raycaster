#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "map.h"
#include "npc.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define FRAME_LIMIT_FPS 60
#define FRAME_LIMIT_MS (1000.0 / FRAME_LIMIT_FPS)
#define FLOOR_BRIGHTNESS_MIN 15
#define FLOOR_BRIGHTNESS_MAX 120

typedef struct {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} Color;

typedef struct {
	unsigned int *pixelsArr;
	int width;
	int height;
	SDL_PixelFormat *format;
} Screen;


extern double fov;
extern double maxRenderDist;
extern Color backgroundColor;
extern bool limitFramerate;


void draw_pixel(Screen *scr, int x, int y, Color color);
void draw_rect(Screen *scr, int xstart, int ystart, int xlen, int ylen, Color color);
void screen_fill(Screen *scr, Color color);
void screen_clear(Screen *scr);
void cap_framerate(double deltaTime);
void render(Screen *screen, Player *player, Map *map, Npc *npcs);

#endif
