
#include "mainAux.h"
#include "settings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int exit = 0;
	mode_e mode = INIT;
	command_e command;
	char *fname;
	int x = -1, y = -1, z = -1;
	int mark_errors = 1;

	/*while the user does not exit, start new game*/
	while(!exit) {
		while (1) {
			fname = (char*) calloc(MAX_SIZE, sizeof(char));
			if (fname == NULL){
				printf("Error: calloc has failed\n ***edit error***");
				fflush(stdout);
				//return 0;
			}
			fflush(stdout);

			command = getCommand(mode, &x, &y, &z, fname);
			printf("%d, %d, %d, %s, %d, %d\n", x, y, z, fname, (int)command, (int)mode);
			fflush(stdout);
			if (command == exit_game) {
				exit = 1;
				break;
			} else if (command == solve) {
				mode = SOLVE;
			} else if (command == edit) {
				mode = EDIT;
			} else {
				if (isWin()) {
					mode = INIT;
				} else {
					executeCommand(mode, command, x, y, z, fname);
				}
			}

		}
		if (exit == 1) {
			printf( "Exiting...");
		}

	}
	return 1;
}



