#include <stdlib.h>

#include "util.h"

// For qsort
int vec2d_compare_x(const void *a, const void *b)
{
	const Vec2d *v1 = (const Vec2d *) a;
	const Vec2d *v2 = (const Vec2d *) b;

	return (v1->x > v2->x) - (v2->x > v1->x); // 1 if greater, 0 if equal, -1 if less
}
