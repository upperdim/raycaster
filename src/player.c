#include <math.h>
#include "player.h"
#include "controls.h"
#include "map.h"
#include "npc.h"

void player_move(Player *player, Keys *keys, Map *map, double delta)
{
	if (keys->up && !keys->down) {
		double newposx = player->posx + sin(player->angle) * player->walkingspeed * delta;
		double newposy = player->posy + cos(player->angle) * player->walkingspeed * delta;

		if (!is_wall(map_get(map, (int) newposx, (int) newposy))) {
			player->posx = newposx;
			player->posy = newposy;
		}
	}

	if (keys->down && !keys->up) {
		double newposx = player->posx - sin(player->angle) * player->walkingspeed * delta;
		double newposy = player->posy - cos(player->angle) * player->walkingspeed * delta;

		if (!is_wall(map_get(map, (int) newposx, (int) newposy))) {
			player->posx = newposx;
			player->posy = newposy;
		}
	}

	if (keys->left && !keys->right)
		player->angle += player->turningspeed * delta;

	if (keys->right && !keys->left)
		player->angle -= player->turningspeed * delta;
}

void player_attack(Player *player, struct Keys *keys, struct Map *map, struct s_Npc *npcs)
{
	// TBA
}
