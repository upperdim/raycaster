#ifndef __UTIL_H_
#define __UTIL_H_

#define PI 3.1415
#define dt_ms(oldtime) (clock() - (oldtime)) / (CLOCKS_PER_SEC / 1000)
#define deg_to_rad(deg) ((PI / 180) * deg)

typedef struct {
	double x, y;
} Vec2d;

int vec2d_compare_x(const void *, const void *);

#endif