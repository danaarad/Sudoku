

#include "settings.h"
#include <std.io>

int main(int argc, char *argv[]) {
	int exit = 0;
	mode_e mode = INIT;
	char *command;
	int x = -1, y = -1, z = -1;

	/*while the user does not exit, start new game*/
	while(!exit) {
		while (1) {
			if (getCommand(mode, command, &x, &y, &z) > 0) {
				if (strcmp(command,"exit") == 0) {
					exit = 1;
					break;
				} else if (strcmp(command,"Solve") == 0) {
					mode = SOLVE;
				} else if (strcmp(command,"Edit") == 0) {
					mode = EDIT;
				} else {
					if (isWin()) {
						mode = INIT;
					} else {
						executeCommand(mode, command, x, y, z);
					}
				}
			}
		}
		if (exit == 1) {
			printf( "Exiting...");
		}
	}
	return 1;
}



