#include "settings.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int getCommand(mode_e mode, char *command_p, int *x_p, int *y_p, int *z_p){
	char *str = (char*) calloc(MAX_SIZE, sizeof(char));
	int valid = 0;
	int parsed;

	if (str == NULL) {
		printf("Error: calloc has failed\n ***edit error***");
		return -1;
	}

	 /*
	 * get command string, ignore \n
	 */
	while (valid == 0) {
		printf("Enter your command:\n");
		if (fgets(str, MAX_SIZE, stdin) == NULL){
			strcpy(str, "exit");
			valid = 1;
		}
		while ((strcmp(str,"\n") == 0)  || (strcmp(str,"\r\n") == 0)) {
			if (fgets(str, MAX_SIZE, stdin) == NULL){
				strcpy(str, "exit");
				valid = 1;
			}
		}

		if ((parsed = parse(str, command_p, x_p, y_p, z_p)) == 0) {
			printf("ERROR: invalid command\n");
			free(str);
			return 0;
		} else if (parsed == 1) {
			valid = 1;
		}
	}
	free(str);
	return 1;
}

/*
 * performs parsing of str <"command x y z"> to its tokens
 * placing tokens in pointer location, respectivly
 *
 * returns 1 if success, 0 else.
 */
int parse(char str[], char *command, int *x_pointer, int *y_pointer, int *z_pointer) {
	const char delim[2] = " ";
	char *token = {0};

	token = strtok(str, delim);
	if (sscanf(token, "%s", command) != 1) {
		return -1;
	}

	if ((strcmp(command, "exit") == 0) || (strcmp(command, "restart") == 0) || (strcmp(command, "validate") == 0)) {
		return 1;
	} else if ((strcmp(command, "hint") == 0)  || (strcmp(command, "set") == 0)){
		token = strtok(NULL, delim);
		if ((token == NULL) ||(sscanf(token, "%d", x_pointer) != 1)) {
			return 0;
		}

		token = strtok(NULL, delim);
		if ((token == NULL) || (sscanf(token, "%d", y_pointer) != 1)) {
			return 0;
		}

		if (strcmp(command, "set") == 0) {
			token = strtok(NULL, delim);
			if ((token == NULL) ||(sscanf(token, "%d", z_pointer) != 1)) {
				return 0;
			}
		}
		return 1;
	}
	return 0;

	}

int executeCommand(mode_e mode, char *command, int *x, int *y, int *z) {
}

void printSeperator(FILE* file_ptr){
	int  i = 0;
	int numofchars = ( 4*BLOCK_HEIGHT*BLOCK_WIDTH + BLOCK_HEIGHT + 1 );

	for (i = 0; i < numofchars; ++i) {
		fprintf(file_ptr, "-");
	}
	printf("\n");
}

void printBoard(FILE* file_ptr) {

	int i = 0, j = 0, k = 0, l = 0, x = 0, y = 0;

	/* i is my block y */
	for (i = 0; i < BLOCKS_IN_COL; ++i) {
		printSeperator(file_ptr);
		/* j is my local y */
		for (j = 0; j < BLOCKS_IN_ROW; ++j) {
			fprintf(file_ptr,"|");
			/*is my block x*/
			for (k=0; k<BLOCK_HEIGHT; ++k) {
				/*is my local x*/
				for(l=0; l<BLOCK_WIDTH; ++l) {
					x = (k * BLOCK_WIDTH) + l + 1;
					y = (i * BLOCK_HEIGHT) + j + 1;

					if (getNodeValue(x,y) != 0) {
						fprintf(file_ptr," %2d",getNodeValue(x,y));
						if (getNodeGiven(x, y) == 1) {
							fprintf(file_ptr,".");
						}else if(getNodeError(x, y) == 1){
							fprintf(file_ptr,"*");
						}else {
							fprintf(file_ptr," ");
						}
					} else {
						fprintf(file_ptr,"    ");
					}
				}
				fprintf(file_ptr,"|");
			}
			fprintf(file_ptr,"\n");
		}
	}
	printSeperator(file_ptr);
	fflush(file_ptr);
}
