#ifndef __PLAYER_H_
#define __PLAYER_H_

struct Map;
struct s_Npc;
struct Keys;

typedef struct {
	double posx;
	double posy;
	double angle;
	double walkingspeed;
	double turningspeed;
} Player;

void player_move(Player *player, struct Keys *keys, struct Map *map, double delta);
void player_attack(Player *player, struct Keys *keys, struct Map *map, struct s_Npc *npcs);

#endif
