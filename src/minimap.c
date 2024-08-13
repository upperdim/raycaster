#include <math.h>
#include "minimap.h"

static void	draw_line_from_player(Screen *screen, Player *player, float scaleHoriz, float scaleVert, float angleOffset)
{
	for (float frontDist = 1; frontDist > 0; frontDist -= .05) {
		float frontPointX = player->posx + frontDist * sin(player->angle + angleOffset);
		float frontPointY = player->posy + frontDist * cos(player->angle + angleOffset);
		draw_rect(screen, frontPointX * scaleHoriz, frontPointY * scaleVert, 2, 2, (Color) {220, 50, 0, 255});
	}
}

void draw_minimap(Screen *screen, Player *player, Map *map, Npc *npcs)
{
	const int MINIMAP_TRANSPARENCY_ALPHA = 50;
	const Color PLAYER_COLOR = {255, 127, 0, MINIMAP_TRANSPARENCY_ALPHA};
	const Color WALL_COLOR = {175, 175, 175, MINIMAP_TRANSPARENCY_ALPHA};
	const Color SPACE_COLOR = {5, 5, 5, MINIMAP_TRANSPARENCY_ALPHA};

	float scaleHorizontal = (screen->width  / 3) / map->width;
	float scaleVertical   = (screen->height / 3) / map->height;

	// Draw background of minimap
	draw_rect(
		screen,
		0,
		0,
		scaleHorizontal * map->width,
		scaleVertical * map->height,
		(Color) {50, 50, 50, MINIMAP_TRANSPARENCY_ALPHA});

	// Draw map tiles
	int tile_width  = 1 * scaleHorizontal;
	int tile_height = 1 * scaleVertical;

	for (int mapY = 0; mapY < map->height; ++mapY) {
		for (int mapX = 0; mapX < map->width; ++mapX) {
			draw_rect(
				screen,
				mapX * tile_width,
				mapY * tile_height,
				tile_width - 1,
				tile_height - 1,
				map->data[mapY * map->width + mapX] == '#' ? WALL_COLOR : SPACE_COLOR);
		}
	}

	// Draw player
	draw_rect(screen, player->posx * scaleHorizontal - 1, player->posy * scaleVertical - 1, 3, 3, PLAYER_COLOR);

	// Draw player direction
	draw_line_from_player(screen, player, scaleHorizontal, scaleVertical, 0);

	// Draw player rays
	// float raycast_angle_step = game->fov / game->scr_width;
	// for (float angle_offset = -game->fov / 2; angle_offset <= +game->fov / 2; angle_offset += raycast_angle_step) {
	// draw_line_from_player(game, scale_horizontal, scale_vertical, angle_offset);
	// }
}
