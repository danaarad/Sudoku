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
#include "Action.h"
#include "solver.h"
#include "printer.h"
#include "arrayAux.h"
#include "file_handler.h"
#include "commandsAux.h"

int doSave(Game* gp, char *fileName){
	FILE* file_ptr = NULL;
		if (!isErrornousBoard(gp)){
			if (isSolvable(gp)){
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

int doReset() {
	printf("doReset!");
		fflush(stdout);
		return 1;
}


int doAutofill(Game *game) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int *possible_vals_arr;
	int num_of_possible_vals = 0;
	int auto_value = 0;

	if (game->isErrornous == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 0;
	}

	//initTempBoard(game);
	for (x = 0; x < N; ++x) {
		for (y = 0; y < N; ++y) {
			possible_vals_arr = calloc(N, sizeof(int));
			if (possible_vals_arr == NULL) {
				printf(CALLOC_ERROR);
				return 0;
			}

			get_possible_values_for_node(game, x, y, possible_vals_arr);
			num_of_possible_vals = filled_cells(possible_vals_arr);
			if (num_of_possible_vals == 1) {
				auto_value = get_first_value(possible_vals_arr);
				setNodeValByType(game, TEMP, x, y, auto_value);
				printf("Cell <%d,%d> set to %d\n", (x+1), (y+1), auto_value);
			}

			free(possible_vals_arr);
		}
	}
	moveAutoFillToValue(game);
	printBoard(game, VALUE);
	return 1;
}

int doGetNumofSols(Game *game) {
	int num_of_sols = 0;
	if (game->isErrornous == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 0;
	}

	if ((num_of_sols = exhaustive_backtracking(game)) == -1) {
		printBoard(game, VALUE);
		return 0;
	}

	printf("Number of solutions: %d\n", num_of_sols);
	if (num_of_sols == 1) {
		printf("This is a good board!\n");
	} else if (num_of_sols > 1) {
		printf("The puzzle has more than 1 solution, try to edit it further\n");
	}
	printBoard(game, VALUE);
	return 1;
}
int doHint(Game *game, char *x, char *y) {
	int N = game->blockHeight * game->blockWidth;
	int x_val = 0, y_val = 0, hint_val = 0;
	int ILP_result = 0;

	x_val = atoi(x);
	y_val = atoi(y);
	if (validate_values_for_hint(x_val, y_val, N) != 1) {
		printf("Error: value not in range 1-%d\n", N);
		printBoard(game, VALUE);
		return 0;
	}

	x_val -= 1;
	y_val -= 1;

	if (game->isErrornous == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 0;
	}
	if (getNodeValByType(game, ISGIVEN, x_val, y_val) == 1) {
		printf("Error: cell is fixed\n");
		printBoard(game, VALUE);
		return 0;
	}
	if (getNodeValByType(game, VALUE, x_val, y_val) != 0) {
		printf("Error: cell already contains a value\n");
		printBoard(game, VALUE);
		return 0;
	}

	ILP_result = fill_nodes_ILP(game);
	if (ILP_result == 1) {
		hint_val = getNodeValByType(game, SOLUTION, x_val, y_val);
		printf("Hint: set cell to %d\n", hint_val);
		printBoard(game, VALUE);
		return 1;
	} else if (ILP_result == 0) {
		printf("Error: board is unsolvable\n");
		printBoard(game, VALUE);
		return 1;
	}

	printBoard(game, VALUE);
	return 0;

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

int doValidate(Game *game) {
	int solvable = 0;

	if (game->isErrornous == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 1;
	}
	solvable = isSolvable(game);
	if (solvable == 1) {
		printf("Validation passed: board is solvable\n");
	} else if (solvable == 0) {
		printf("Validation failed: board is unsolvable\n");
	} else {
		printBoard(game, VALUE);
		return 0;
	}
	printBoard(game, VALUE);
	return 1;
}

int doSet(Game *game, char *x, char *y, char *z) {
	int x_val = 0, y_val = 0, z_val = 0;
	int N = game->blockHeight * game->blockWidth;
	Action *new_action;
	int val_before;

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
		game->filledNodes++; }
	if (z_val == 0){
		game->filledNodes--; }

	val_before = getNodeValByType(game, VALUE, x, y);
	setNodeValByType(game, VALUE, x_val , y_val, z_val);

	new_action = (Action *) initAction(x_val, y_val, val_before, z_val, game->LatestAction, 0);
	if (new_action == NULL) {
		printBoard(game, VALUE);
		return 0;
	}
	UpdateErrorsByCell(game, x_val, y_val);
	printBoard(game, VALUE);
	return 1;
}

int doGenerate(Game *game, char *x, char *y) {
	int N = game->blockHeight * game->blockWidth;
	int E = (N*N) - game->filledNodes;
	int x_val = 0, y_val = 0;
	int attempt;

	x_val = atoi(x);
	y_val = atoi(y);
	if (validate_values_for_generate(x_val, x, y_val, y, E) != 1) {
		printf("Error: value not in range 0-%d\n", E);
		printBoard(game, VALUE);
		return 0;
	}

	if (game->filledNodes != 0) {
		printf("Error: board is not empty\n");
		printBoard(game, VALUE);
		return 0;
	}
	for (attempt = 0; attempt < RETRY_ATTEMPTS_FOR_GENERATE; ++attempt) {
		if (fill_nodes_random(game, x_val) != 1) {
			continue;
		}
		if (fill_nodes_ILP(game) != 1) {
			continue;
		}
		if (clear_nodes(game, y_val) != 1) {
			continue;
		}
		printBoard(game, VALUE);
		return 1;
	}
	printf("Error: puzzle generator failed\n");
	printBoard(game, VALUE);
	return 0;

}

