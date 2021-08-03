#include <stdio.h>
#include <stdbool.h>

#include "debug.h"

bool debugMode = false;
bool debugOutOfScreenFlag = false;

void print_debug_info(Player *p, double deltaTime)
{
	if (debugMode) {
		printf("x: %.2lf - y: %.2lf - a: %.2lf - dt: %lf - FPS: %d\n", 
					p->posx, p->posy, p->angle, deltaTime, (int) (1000 / deltaTime));
	}
}
