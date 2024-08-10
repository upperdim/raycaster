#ifndef __PLAYER_H_
#define __PLAYER_H_

struct Map;
struct Keys;

typedef struct {
	double posx;
	double posy;
	double angle;
	double walkingspeed;
	double turningspeed;
} Player;

void move_player(Player *player, struct Keys *keys, struct Map *map, double delta);

#endif
