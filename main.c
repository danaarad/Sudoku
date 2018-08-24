
#include "mainAux.h"
#include "settings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
			command = (char*) calloc(MAX_SIZE, sizeof(char));
			fname = (char*) calloc(MAX_SIZE, sizeof(char));

			if (command == NULL || fname == NULL){
				printf("Error: calloc has failed\n ***edit error***");
				fflush(stdout);
				//return 0;
			}
			fflush(stdout);

			if (getCommand(mode, command, &x, &y, &z, fname) > 0) {
				printf("%d, %d, %d, %s, %s, %d\n", x, y, z, fname, command, mode);
				fflush(stdout);
				if (strcmp(command,"exit") == 0) {
					exit = 1;
					break;
				} else if (strcmp(command,"solve") == 0) {
					mode = SOLVE;
				} else if (strcmp(command,"edit") == 0) {
					mode = EDIT;
				} else {
					if (isWin()) {
						mode = INIT;
					} else {
						executeCommand(mode, command, x, y, z, fname);
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



