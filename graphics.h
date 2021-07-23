#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <SDL2/SDL.h>

#define FRAME_LIMIT_FPS 60
#define FRAME_LIMIT_MS (1000 / FRAME_LIMIT_FPS)
#define FLOOR_BRIGHTNESS_MIN 15
#define FLOOR_BRIGHTNESS_MAX 200

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

double fov;
double maxRenderDist;
Color backgroundColor;

void draw_pixel(Screen *, int, int, Color);
void draw_rect(Screen *, int, int, int, int, Color);
void screen_fill(Screen *, Color);
void screen_clear(Screen *);

#endif