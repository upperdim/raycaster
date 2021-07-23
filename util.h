#ifndef __UTIL_H_
#define __UTIL_H_

#define dt_ms(oldtime) (clock() - (oldtime)) / (CLOCKS_PER_SEC / 1000)

typedef struct {
	double x, y;
} Vec2d;

#endif