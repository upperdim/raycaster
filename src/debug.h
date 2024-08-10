#ifndef __DEBUG_H_
#define __DEBUG_H_

#include "player.h"

extern bool debugMode;
extern bool debugOutOfScreenFlag;


void print_debug_info(Player *, double deltaTime);


#endif