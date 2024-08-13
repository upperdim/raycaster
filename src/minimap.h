#ifndef __MINIMAP_H_
#define __MINIMAP_H_

#include "graphics.h"
#include "player.h"
#include "map.h"
#include "npc.h"

void draw_minimap(Screen *screen, Player *player, Map *map, Npc *npcs);

#endif
