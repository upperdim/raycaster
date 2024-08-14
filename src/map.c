#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map.h"

void map_print(Map *m)
{
	for (int i = 0; i < m->height; ++i) {
		for (int j = 0; j < m->width; ++j) {
			putchar(map_get(m, j, i));
		}
		putchar('\n');
	}
}

Map map_import(char *mappath)
{
	FILE *mapfile = fopen(mappath, "rb");
	if (mapfile == NULL) {
		printf("Error! Failed opening file %s\n", mappath);
		exit(EXIT_FAILURE);
	}

	fseek(mapfile, 0, SEEK_END);
	long len = ftell(mapfile);
	fseek(mapfile, 0, SEEK_SET);

	Map map = {0};
	map.data = (char *) calloc(len + 1, sizeof(char));
	if (map.data == NULL) {
		printf("Error! Failed allocating memory.\n");
		exit(EXIT_FAILURE);
	}

	int ch;
	int mapIndex = 0;
	int currRowLen = 0, prevRowLen = 0, rowCnt = 0;
	int isFirstRun = true;
	while ((ch = fgetc(mapfile)) != EOF) {
		switch (ch) {
		case '\n':
			// Detect map width from the first line
			if (isFirstRun) {
				isFirstRun = false;
				map.width = currRowLen;
			} else if (currRowLen != prevRowLen) {
				// Don't allow different row widths in map
				printf("Error! Map has rows with different size!\n");
				exit(EXIT_FAILURE);
			}

			prevRowLen = currRowLen;
			currRowLen = 0;

			// Keep track of number of rows in order to detect map height
			++rowCnt;
			break;
		// Ignore windows newline characters
		case '\r':
			break;
		// Insert non-newline characters into map data
		default:
			++currRowLen;
			map.data[mapIndex++] = ch;
			break;
		}
	}
	++rowCnt; // gets updated on newlines only, didnt increment in the very last line ending with EOF
	map.height = rowCnt;
	map.data[mapIndex] = '\0';

	fclose(mapfile);
	return map;
}

char get_player_tile(Map *m, Player *p)
{
	return m->data[(int) p->posx * m->width + (int) p->posy];
}

int is_wall(char mapElement)
{
	switch (mapElement) {
	case '#': return true;
	default : return false;
	}
}

int is_out_of_bounds(Map *m, int x, int y)
{
	return x < 0 || x >= m->width || y < 0 || y >= m->height;
}

char map_get(Map *m, int x, int y)
{
	return (m->data[y * m->width + x]);
}
