#include <math.h>
#include "player.h"
#include "controls.h"
#include "map.h"

void move_player(Player *player, Keys *keys, Map *map, double delta)
{
	if (keys->up && !keys->down) {
		double newposx = player->posx + sin(player->angle) * player->walkingspeed * delta;
		double newposy = player->posy + cos(player->angle) * player->walkingspeed * delta;

		if (!is_wall(map->data[(int) newposx * map->width + (int) newposy])) {
			player->posx = newposx;
			player->posy = newposy;
		}
	}

	if (keys->down && !keys->up) {
		double newposx = player->posx - sin(player->angle) * player->walkingspeed * delta;
		double newposy = player->posy - cos(player->angle) * player->walkingspeed * delta;

		if (!is_wall(map->data[(int) newposx * map->width + (int) newposy])) {
			player->posx = newposx;
			player->posy = newposy;
		}
	}

	if (keys->left && !keys->right)
		player->angle -= player->turningspeed * delta;

	if (keys->right && !keys->left)
		player->angle += player->turningspeed * delta;
}
