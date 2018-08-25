/*
 * commands.c
 *
 *  Created on: 11 ���� 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "Game.h"
#include "printer.h"
#include "file_handler.h"

int doSave(Game* gp, char *fileName){
	FILE* file_ptr = NULL;
		if (!isErrornousBoard(gp)){
			if (isSolvableBoard(gp)){
				file_ptr = fopen(fileName,"w");
				if (file_ptr != NULL){//success
					writeToFile(gp, file_ptr);
					printf("Saved to: %s\n",fileName);
					return 0;
				}else{//couldn't open file
					printf("Error: File cannot be created or modified\n");
				}
			}else{ //board is not solvable
				printf("Error: board validation failed\n");
			}
		}else{//there are bad values in the board
			printf( "Error: board contains erroneous values\n");
		}
	return 0;
	}

int doExit() {
	printf("doExit!");
	fflush(stdout);
	return 1;
}
int doReset() {
	printf("doReset!");
		fflush(stdout);
		return 1;
}
int doAutofill() {
	printf("doAutofill!");
		fflush(stdout);
		return 1;
}
int doGetNumofSols() {
	printf("doGetNumofSols!");
		fflush(stdout);
		return 1;
}
int doHint(int x, int y) {
	printf("doHint!");
		fflush(stdout);
		return 1;
}

int doEditFile(Game *game, char *fileName)  {
	FILE *f_pointer = fopen(fileName, "r");

	printf("doEditFile!\n");

	if (f_pointer == NULL) {
		printf("Error: File cannot be opened\n");
		return 0;
	}
	*game = *readFromFile(f_pointer);
	game->mode = EDIT;
	printBoard(game, VALUE);
	return 1;
}

int doSolveFile(Game *game, char *fileName) {
	FILE *f_pointer = fopen(fileName, "r");

	printf("doSolveFile!\n");

	if (f_pointer == NULL) {
		printf("Error: File doesn't exist or cannot be opened\n");
		return 0;
	}
	*game = *readFromFile(f_pointer);
	game->mode = SOLVE;
	printBoard(game, VALUE);
	return 1;
}

int doUndo() {
	printf("doUndo!");
		fflush(stdout);
		return 1;
}

int doRedo() {
	printf("doRedo!");
		fflush(stdout);
		return 1;
}

int doMarkErrors(Game *game, int x) {
	printf("doMarkErrors!\n");
	if (x == 0 || x == 1) {
		game->markErrors = x;
		return 1;
	}
	printf("Error: the value should be 0 or 1\n");
	return 0;
}

int doValidate() {
	printf("doValidate!");
		fflush(stdout);
		return 1;
}
int doSet(int x, int y, int z) {
	printf("doSet!");
		fflush(stdout);
		return 1;
}
int doGenerate(int x, int y) {
	printf("doGenerate!");
		fflush(stdout);
		return 1;
}

