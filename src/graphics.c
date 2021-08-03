#include <stdbool.h>

#include "graphics.h"
#include "debug.h"

double fov = 3.14159 / 2.5;
double maxRenderDist = 16.0;
Color backgroundColor = {255, 0, 0, 0};
bool limitFramerate = false;

void draw_pixel(Screen *scr, int x, int y, Color c)
{
	if (x < 0 || x > scr->width || y < 0 || y > scr->height) {
		debugOutOfScreenFlag = true;
		return;
	}

	scr->pixelsArr[x + y * scr->width] = SDL_MapRGBA(scr->format, c.r, c.g, c.b, c.a);
}

void draw_rect(Screen *scr, int xstart, int ystart, int xend, int yend, Color c)
{
	for (int i = ystart; i < yend; ++i) {
		for (int j = xstart; j < xend; ++j) {
			draw_pixel(scr, i, j, c);
		}
	}
}

void screen_fill(Screen *scr, Color c)
{
	draw_rect(scr, 0, 0, scr->height, scr->width, c);
}

void screen_clear(Screen *scr)
{
	screen_fill(scr, backgroundColor);
}

void cap_framerate(double deltaTime)
{
	if (limitFramerate && deltaTime < FRAME_LIMIT_MS) {
		SDL_Delay(FRAME_LIMIT_MS - deltaTime);
	}
}
