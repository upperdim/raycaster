#include <stdio.h>
#include <math.h>
#include "minimap.h"

// Lot of ugly parameters but it gives an accurate representation of FOV in minimap
static void	draw_line_from_player(Screen *screen,
                                  Map *map,
                                  Player *player,
								  float scaleHoriz,
								  float scaleVert,
								  float angleOffset,
								  float lineLen,
								  int thickness,
								  Color lineColor)
{
	for (float frontDist = lineLen; frontDist > 0; frontDist -= .05) {
		float frontPointX = player->posx + frontDist * sin(player->angle + angleOffset);
		float frontPointY = player->posy + frontDist * cos(player->angle + angleOffset);

		if (frontPointX < map->width && frontPointY < map->height) {
			draw_rect(
				screen,
				(frontPointX * scaleHoriz) - thickness / 2,
				(frontPointY * scaleVert) - thickness / 2,
				thickness,
				thickness,
				lineColor);
		}
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
	draw_rect( screen, 0, 0, scaleHorizontal * map->width, scaleVertical * map->height, (Color) {50, 50, 50, MINIMAP_TRANSPARENCY_ALPHA});

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
				map_get(map, mapX, mapY) == '#' ? WALL_COLOR : SPACE_COLOR);
		}
	}

	// Draw player
	draw_rect(screen, player->posx * scaleHorizontal - 1, player->posy * scaleVertical - 1, 3, 3, PLAYER_COLOR);

	// Draw player direction
	// draw_line_from_player(screen, player, scaleHorizontal, scaleVertical, 0, 1, 1, (Color) {150, 50, 50, MINIMAP_TRANSPARENCY_ALPHA});

	// Draw player rays
	const Color FOV_LINE_COLOR = (Color) {50, 50, 125, MINIMAP_TRANSPARENCY_ALPHA};
	const float FOV_LINE_LEN = 16;
	const int FOV_LINE_THICKNESS = 1;

	draw_line_from_player(screen, map, player, scaleHorizontal, scaleVertical, +fov / 2, FOV_LINE_LEN, FOV_LINE_THICKNESS, FOV_LINE_COLOR);
	draw_line_from_player(screen, map, player, scaleHorizontal, scaleVertical, -fov / 2, FOV_LINE_LEN, FOV_LINE_THICKNESS, FOV_LINE_COLOR);
	
	// Draw all rays
	// float raycast_angle_step = fov / screen->width;
	// for (float angle_offset = -fov / 2; angle_offset <= fov / 2; angle_offset += raycast_angle_step) {
	// 	draw_line_from_player(screen, player, scaleHorizontal, scaleVertical, angle_offset);
	// }
}
