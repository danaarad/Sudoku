#include "mainAux.h"
#include "parser.h"
#include "settings.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int isWin(){
	return 0;
}

command_e getCommand(mode_e mode, int *x_p, int *y_p, int *z_p, char *fname_p){
	char *str = (char*) calloc(MAX_SIZE, sizeof(char));
	int valid = 0;
	int parsed;
	command_e command = 0;

	if (str == NULL) {
		printf("Error: calloc has failed\n ***edit error***");
		fflush(stdout);
		return -1;
	}
	printf("Enter your command:\n");
	fflush(stdout);
	 /*
	 * get command string, ignore \n
	 */
	while (valid == 0) {
		if (fgets(str, MAX_SIZE, stdin) == NULL){
			strcpy(str, "exit");
			break;
		}

		while ((strcmp(str,"\n") == 0)  || (strcmp(str,"\r\n") == 0)) {
			if (fgets(str, MAX_SIZE, stdin) == NULL){
				strcpy(str, "exit");
				valid = 1;
			}
		}

		if ((parsed = parse(str, &command, x_p, y_p, z_p, fname_p)) == 0) {
			printf("ERROR: invalid command\n");
			printf("Enter your command:\n");
			fflush(stdout);
		} else if (parsed == 1) {
			valid = 1;
		}
	}
	free(str);
	return command;
}


int executeCommand(mode_e mode, command_e command, int *x, int *y, int *z, char *fname) {
	return 0;
}

