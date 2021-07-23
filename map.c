#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map.h"

void map_print(Map *m)
{
	for (int i = 0; i < m->height; ++i) {
		for (int j = 0; j < m->width; ++j) {
			putchar(m->data[i * m->width + j]);
		}
		putchar('\n');
	}
}

Map map_import(char *mappath)
{
	FILE *mapfile = fopen(mappath, "rb");
	if (mapfile == NULL) {
		printf("Error! Failed opening file %s\n", mappath);
		exit(1);
	}

	fseek(mapfile, 0, SEEK_END);
	long len = ftell(mapfile);
	fseek(mapfile, 0, SEEK_SET);

	Map map = {0};
	map.data = (char *) calloc(len + 1, sizeof(char));
	if (map.data == NULL) {
		printf("Error! Failed allocating memory.\n");
		exit(2);
	}

	char ch;
	int mapIndex = 0;
	int currRowLen = 0, prevRowLen = 0, rowCnt = 0;
	int isFirstRun = true;
	while ((ch = fgetc(mapfile)) != EOF) {
		switch (ch) {
		case '\n':
			if (isFirstRun) {
				isFirstRun = false;
				map.width = currRowLen;
			} else if (currRowLen != prevRowLen) {
				printf("Error! Map has rows with different size!\n");
				exit(3);
			}

			prevRowLen = currRowLen;
			currRowLen = 0;

			++rowCnt;
			break;
		case '\r':
			break;
		default:
			++currRowLen;
			map.data[mapIndex++] = ch;
			break;
		}
	}
	++rowCnt; // gets updated on newlines only, didnt increment in the very last line ending with EOF
	fclose(mapfile);

	map.data[mapIndex] = '\0';
	map.height = rowCnt;

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
