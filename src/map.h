#ifndef __MAP_H_
#define __MAP_H_

#include "player.h"

typedef struct {
	char *data;
	int height;
	int width;
} Map;

void map_print(Map *);
Map map_import(char *);
char get_player_tile(Map *, Player *);
int is_wall(char);
int is_out_of_bounds(Map *m, int x, int y);

#endif