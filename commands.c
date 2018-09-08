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
#include "change.h"


/*
 * Execute save command
 * Returns 1 on success, 0 on failure
 */
int doSave(Game* gp, char *fileName){
	FILE* file_ptr = NULL;
		if (!isErrornousBoard(gp)){
			if (isSolvable(gp)){
				file_ptr = fopen(fileName,"w");
				if (file_ptr != NULL){
					/*success*/
					writeToFile(gp, file_ptr);
					printf("Saved to: %s\n",fileName);
					return 0;
				}else{
					/*couldn't open file*/
					printf("Error: File cannot be created or modified\n");
				}
			}else{
				/*board is not solvable*/
				printf("Error: board validation failed\n");
			}
		}else {
			/*there are bad values in the board*/
			printf( "Error: board contains erroneous values\n");
		}
	return 0;
	}

/*
 * Execute undo command
 * Returns 1 on success, 0 on failure
 */
int doUndo(Game *game) {
	Action *action_to_undo = game->LatestAction;
	if (action_to_undo->type != INIT_A) {
		undoAction(game, 1);
		game->LatestAction = action_to_undo->prev_action;
		if (action_to_undo->type == GENERATE_A) {
			printf("Undo Generate\n");
		}
		UpdateErrors(game);
	} else {
		printf("Error: no moves to undo\n");
	}
	printBoard(game, VALUE);
	return 1;
}


/*
 * Execute redo command
 * Returns 1 on success, 0 on failure
 */
int doRedo(Game *game) {
	Action *action_to_redo;
	if (game->LatestAction != NULL) {
		action_to_redo = game->LatestAction->next_action;
		if (action_to_redo != NULL) {
			game->LatestAction = action_to_redo;
			redoAction(game, 1);
			if (action_to_redo->type == GENERATE_A) {
				printf("Redo Generate\n");
			}
			UpdateErrors(game);
			printBoard(game, VALUE);
			return 1;
		}
	}
	printf("Error: no moves to redo\n");
	printBoard(game, VALUE);
	return 1;
}


/*
 * Execute reset command
 * Returns 1 on success, 0 on failure
 */
int doReset(Game *game) {
	Action *prev_action = NULL;

	while (game->LatestAction->type != INIT_A) {
		undoAction(game, 0);
		prev_action = game->LatestAction;
		game->LatestAction = game->LatestAction->next_action;
	}
	freeActionsAfter(prev_action);
	freeSingleAction(prev_action);
	printf("Board reset\n");
	printBoard(game, VALUE);
	return 1;

}

/*
 * Execute autofill command
 * Returns 1 on success, 0 on failure
 */
int doAutofill(Game *game) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int *possible_vals_arr;
	int num_of_possible_vals = 0;
	int auto_value = 0;
	int value;

	if (isErrornousBoard(game) == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 0;
	}

	initTempBoard(game);
	for (y = 0; y < N; ++y) {
		for (x = 0; x < N; ++x) {
			possible_vals_arr = calloc(N, sizeof(int));
			if (possible_vals_arr == NULL) {
				printf(CALLOC_ERROR);
				return 0;
			}

			value = getNodeValByType(game, VALUE, x, y);
			get_possible_values_for_node(game, VALUE, x, y, possible_vals_arr);
			num_of_possible_vals = filled_cells(possible_vals_arr, game->N);
			if (num_of_possible_vals == 1 && value == 0) {
				auto_value = get_first_value(possible_vals_arr, game->N);
				setNodeValByType(game, TEMP, x, y, auto_value);
				printf("Cell <%d,%d> set to %d\n", (x+1), (y+1), auto_value);
			}

			free(possible_vals_arr);
		}
	}
	if (moveTempToValue(game, SET_A) != 1) {
		printBoard(game, VALUE);
		return 0;
	}
	printBoard(game, VALUE);
	return 1;
}


/*
 * Execute num_solutions command
 * Returns 1 on success, 0 on failure
 */
int doGetNumofSols(Game *game) {
	int num_of_sols = 0;
	if (isErrornousBoard(game) == 1) {
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
	int N = game->N;
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

	if (isErrornousBoard(game) == 1) {
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

	ILP_result = fill_nodes_ILP(game, VALUE);
	if (ILP_result == GRB_OPTIMAL) {
		hint_val = getNodeValByType(game, TEMP, x_val, y_val);
		printf("Hint: set cell to %d\n", hint_val);
		printBoard(game, VALUE);
		return 1;
	} else {
		printf("Error: board is unsolvable\n");
		printBoard(game, VALUE);
		return 1;
	}

	printBoard(game, VALUE);
	return 0;

}


/*
 * Execute edit from file command
 * Returns 1 on success, 0 on failure
 */
int doEditFile(Game **game, char *fileName)  {
	FILE *f_pointer = fopen(fileName, "r");

	printf("doEditFile!\n");

	if (f_pointer == NULL) {
		printf("Error: File cannot be opened\n");
		return 0;
	}
	freeGame(*game);
	*game = readFromFile(f_pointer);
	(*game)->mode = EDIT;
	UpdateErrors(*game);
	printBoard(*game, VALUE);
	return 1;
}

/*
 * Execute solve command
 * Returns 1 on success, 0 on failure
 */
int doSolveFile(Game **game, char *fileName) {
	FILE *f_pointer = fopen(fileName, "r");
	if (f_pointer == NULL) {
		printf("Error: File doesn't exist or cannot be opened\n");
		return 0;
	}

	freeGame(*game);
	*game = readFromFile(f_pointer);
	fclose(f_pointer);
	if (*game == NULL) {
		return 0;
	}
	(*game)->mode = SOLVE;
	UpdateErrors(*game);
	printBoard(*game, VALUE);
	return 1;
}

/*
 * Execute mark_errors command
 * Returns 1 on success, 0 on failure
 */
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


/*
 * Execute validate command
 * Returns 1 on success, 0 on failure
 */
int doValidate(Game *game) {
	int solvable = 0;

	if (isErrornousBoard(game) == 1) {
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


/*
 * Execute set command
 * Returns 1 on success, 0 on failure
 */
int doSet(Game *game, char *x, char *y, char *z) {
	int x_val = 0, y_val = 0, z_val = 0;
	int N = game->blockHeight * game->blockWidth;
	Action *new_action; Change *new_change;
	int val_before;

	/*cast to int and validate values*/
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

	/*if cell is fixed*/
	if (getNodeValByType(game, ISGIVEN, x_val, y_val) == 1) {
		printf("Error: cell is fixed\n");
		printBoard(game, VALUE);
		return 0;
	}

	/*update cell error*/
	if (z_val == 0){
		setNodeValByType(game, ISERROR, x_val , y_val, 0);
	}

	/*set new value and save to redo/undo list*/
	val_before = getNodeValByType(game, VALUE, x_val, y_val);
	setNodeValByType(game, VALUE, x_val , y_val, z_val);

	new_change = (Change *) initChange(x_val, y_val, val_before, z_val, NULL);
	if (new_change == NULL) {
		printBoard(game, VALUE);
		return 0;
	}
	new_action = (Action *) initAction(SET_A, new_change, game->LatestAction);
	if (new_action == NULL) {
		printBoard(game, VALUE);
		return 0;
	}
	game->LatestAction = new_action;
	UpdateErrors(game);
	printBoard(game, VALUE);
	return 1;
}

int doGenerate(Game *game, char *x, char *y) {
	int N = game->blockHeight * game->blockWidth;
	int filled_nodes = CountValuesInBoard(game);
	int E = (N*N) - filled_nodes;
	int x_val = 0, y_val = 0;
	int attempt;

	x_val = atoi(x);
	y_val = atoi(y);
	if (validate_values_for_generate(x_val, x, y_val, y, E) != 1) {
		printf("Error: value not in range 0-%d\n", E);
		printBoard(game, VALUE);
		return 0;
	}

	if (filled_nodes != 0) {
		printf("Error: board is not empty\n");
		printBoard(game, VALUE);
		return 0;
	}
	for (attempt = 0; attempt < RETRY_ATTEMPTS_FOR_GENERATE; ++attempt) {
		initTempBoard(game);
		if (fill_nodes_random(game, TEMP, x_val) != 1) {
			continue;
		}
		printf("filled random %d cells\n", x_val);
		printBoard(game, TEMP);
		if (fill_nodes_ILP(game, TEMP) != GRB_OPTIMAL) {
			continue;
		}
		printf("filled ILP\n");
		printBoard(game, TEMP);
		if (clear_nodes(game, TEMP, y_val) != 1) {
			continue;
		}
		printf("cleared all but %d cells\n", y_val);
		printBoard(game, TEMP);
		if (moveTempToValue(game, GENERATE_A) != 1){
			continue;
		}
		printBoard(game, VALUE);
		return 1;
	}
	printf("Error: puzzle generator failed\n");
	printBoard(game, VALUE);
	return 0;

}

