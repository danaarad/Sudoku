

#include "settings.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	int exit = 0;
	mode_e mode = INIT;
	char *command;
	char *fname;
	int x = -1, y = -1, z = -1;
	int mark_errors = 1;

	/*while the user does not exit, start new game*/
	while(!exit) {
		while (1) {
			if (getCommand(mode, command, &x, &y, &z, fname) > 0) {
				printf("%d, %d, %d, %s, %s\n", x, y, z, fname, command);
				fflush(stdout);
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



