/*
 * commands.c
 *
 *  Created on: 11 баев 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "Game.h"
#include "Node.h"
#include "printer.h"
#include "file_handler.h"
#include "commandsAux.h"

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
int doHint(char *x, char *y) {
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

int doMarkErrors(Game *game, char *x) {
	int mark_errors_value = -1;

	printf("doMarkErrors!\n");

	mark_errors_value = atoi(x);
	if (mark_errors_value == 0 || mark_errors_value == 1) {
		game->markErrors = mark_errors_value;
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
int doSet(Game *game, char *x, char *y, char *z) {
	int x_val = 0;
	int y_val = 0;
	int z_val = 0;
	int N = game->blockHeight * game->blockWidth;

	x_val = atoi(x);
	y_val = atoi(y);
	z_val = atoi(z);

	if (validate_values_for_set(x_val, y_val, z_val, z, N) != 1) {
		printf("Error: value not in range 0-%d\n", N);
		printBoard(game, VALUE);
		return 0;
	}

	x_val -= 1;
	y_val -= 1;

	if (getNodeValByType(game, ISGIVEN, x_val, y_val) == 1) {
		printf("Error: cell is fixed\n");
		printBoard(game, VALUE);
		return 0;
	}

	if (getNodeValByType(game, VALUE, x_val, y_val) == 0){
		game->filledNodes++;
	}
	if (z_val == 0){
		game->filledNodes--;
	}

	setNodeValByType(game, VALUE, x_val , y_val, z_val);
	//check_errors(game)
	//new_action = init action()
	//freeActionsAfter(game->LatestAction);
	//setNextAction(game->LatestAction, new_action)
	//setLatestAction(game, new_action)
	printBoard(game, VALUE);
	return 1;
}
int doGenerate(char *x, char *y) {
	printf("doGenerate!");
		fflush(stdout);
		return 1;
}

