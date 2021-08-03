#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "controls.h"
#include "graphics.h"
#include "debug.h"
#include "game.h"
#include "cli.h"


void print_version()
{
	printf("Ray Caster %s - Author: github.com/upperdim\n", VERSION);
}

void print_help()
{
	print_version();
	putchar('\n');

	printf("Controls:\n");
	printf("  W, Up arrow       Move forward\n");
	printf("  S, Down arrow     Move backwards\n");
	printf("  A, Left arrow     Turn left\n");
	printf("  D, Right arrow    Turn right\n");
	printf("  Q, ESC            Quit\n");
	printf("  V                 Toggle frame limiter on or off.\n");
	printf("                        Limits the framerate to 60.\n");
	putchar('\n');
	
	printf("Arguments:\n");
	printf("  -h, -H, --help       Prints this hint.\n");
	printf("  -v, -V, --version    Prints the version of the binary.\n");
	printf("  -d, -D, --debug      Runs the binary in debugging mode. Prints\n");
	printf("                           player position and angle, time difference\n");
	printf("                           and framerate. Indicates upon window resizing\n");
	printf("                           and frame limiter toggle.\n");
	printf("  -l, -L               Limits framerate to 60.\n");
	putchar('\n');
}

void handle_args(int *argc, char **argv)
{
	for (int i = 1; i < *argc; ++i) {
		if      (strcmp("--help",    argv[i]) == 0) {print_help();    gameOver = true;}
		else if (strcmp("--version", argv[i]) == 0) {print_version(); gameOver = true;}
		else if (strcmp("--debug",   argv[i]) == 0) {debugMode = true;}
		else if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h':
			case 'H':
				print_help();
				gameOver = true;
			case 'v':
			case 'V':
				print_version();
				gameOver = true;
			case 'd':
			case 'D':
				debugMode = true;
				break;
			case 'l':
			case 'L':
				limitFramerate = true;
				break;
			default:
				printf("%s: Unrecognized option '%s'\nTry '%s --help' for more information.\n", argv[0], argv[i], argv[0]);
				gameOver = true;;
			}
		} else {
			printf("%s: Unrecognized option '%s'\nTry '%s --help' for more information.\n", argv[0], argv[i], argv[0]);
			gameOver = true;;
		}
	}
}
