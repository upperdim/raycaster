#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "graphics.h"
#include "debug.h"
#include "util.h"

double fov = deg_to_rad(60);
double maxRenderDist = 16.0;
Color backgroundColor = {255, 0, 0, 0};
bool limitFramerate = false;

void draw_pixel(Screen *scr, int x, int y, Color c)
{
	if (x < 0 || x >= scr->width || y < 0 || y >= scr->height) {
		debugOutOfScreenFlag = true;
		return;
	}

	scr->pixelsArr[x + y * scr->width] = SDL_MapRGBA(scr->format, c.r, c.g, c.b, c.a);
}

void draw_rect(Screen *scr, int xstart, int ystart, int xlen, int ylen, Color c)
{
	const int XLIM = xstart + xlen;
	const int YLIM = ystart + ylen;

	for (int y = ystart; y < YLIM; ++y) {
		for (int x = xstart; x < XLIM; ++x) {
			draw_pixel(scr, x, y, c);
		}
	}
}

void screen_fill(Screen *scr, Color c)
{
	draw_rect(scr, 0, 0, scr->width, scr->height, c);
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

static int is_boundary(Player *player, double distanceToWall, int testX, int testY, double eyeX, double eyeY)
{
	Vec2d tile_corners[4];
	int corner_index = 0;
	for (int tx = 0; tx < 2; tx++) {
		for (int ty = 0; ty < 2; ty++) {
			// Angle of corner to eye
			double vy = (double)testY + ty - player->posy;
			double vx = (double)testX + tx - player->posx;
			double d = sqrt(vx * vx + vy * vy);
			double dot = (eyeX * vx / d) + (eyeY * vy / d);

			tile_corners[corner_index++] = (Vec2d) {d, dot};
		}
	}

	qsort(&tile_corners, 4, sizeof(tile_corners[0]), vec2d_compare_x);

	if (distanceToWall < maxRenderDist) {
		double bound = 0.004;
		if (acos(tile_corners[0].y) < bound || acos(tile_corners[1].y) < bound)
			return 1;
	}

	return 0;
}

static void render_ray(int x, Screen *screen, Player *player, Map *map, Npc *npcs)
{
	double rayAngle = (player->angle + fov / 2.0) - ((double) x / (double) screen->width) * fov;

	double stepSize = 0.1;
	double distanceToWall = 0.0;

	double eyeX = sin(rayAngle);
	double eyeY = cos(rayAngle);

	int testX = 0;
	int testY = 0;

	while (distanceToWall < maxRenderDist) {
		distanceToWall += stepSize;
		testX = (int) (player->posx + eyeX * distanceToWall);
		testY = (int) (player->posy + eyeY * distanceToWall);

		if (is_out_of_bounds(map, testX, testY)) {
			distanceToWall = maxRenderDist;
			break;
		}

		if (is_wall(map_get(map, testX, testY)))
			break;
	}

	int isBoundary = is_boundary(player, distanceToWall, testX, testY, eyeX, eyeY);

	distanceToWall = distanceToWall * cos(rayAngle - player->angle); // correct fisheye

	int ceiling = (double) (screen->height / 2.0) - screen->height / ((double) distanceToWall);
	int floor = screen->height - ceiling;

	Color shade;
	if (isBoundary) {
		shade = (Color) {0, 0, 0, 0};
	} else {
		uint8_t c = 255 - (distanceToWall * 255 / maxRenderDist) + 15;
		shade = (Color) {c, c, c, 255};
	}

	draw_rect(screen, x, 0, 1, ceiling, (Color) {0, 0, 0, 0}); // draw ceiling
	draw_rect(screen, x, ceiling, 1, floor - ceiling, shade);  // draw wall
	
	// Draw floor
	for (int y = floor; y < screen->height; ++y) {
		int half_screen_height = (screen->height-1) / 2;
		uint8_t c = (((FLOOR_BRIGHTNESS_MAX - FLOOR_BRIGHTNESS_MIN) * (y - half_screen_height)) / half_screen_height) + FLOOR_BRIGHTNESS_MIN;
		shade = (Color) {0, c, 0, 255};
		draw_pixel(screen, x, y, shade);
	}
}

void render(Screen *screen, Player *player, Map *map, Npc *npcs)
{
	for (int x = 0; x < screen->width; ++x) {
		render_ray(x, screen, player, map, npcs);
	}
}
