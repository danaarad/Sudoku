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
#include "file_handler.h"
#include "parser.h"
#include "commands.h"


/****************** VALIDATORS ****************/
/*
 * Validates command is compatible with mode, according to project documents.
 * Return 1 if compatible, 0 otherwise
 */
static int validateCommandMode(command_e command, mode_e mode) {
	command_e allowed_init[] = {solve, edit, edit_default, exit_game};
	command_e allowed_edit[] = {solve, edit, edit_default, print_board, set,
			validate, generate, undo, redo, save, num_solutions, reset, exit_game};
	command_e allowed_solve[] = {solve, edit, edit_default, mark_errors, print_board,
			set, validate, save, undo, redo, hint, num_solutions, autofill, reset, exit_game};
	int i = 0;
	int result = 0;

	switch(mode){
	case INIT:
		for(i = 0; i < (int)(sizeof (allowed_init) / sizeof (allowed_init[0])); ++i) {
			if (command == allowed_init[i]) {
				result = 1;
				break;
			}
		}
		break;
	case EDIT:
		for(i = 0; i < (int)(sizeof (allowed_edit) / sizeof (allowed_edit[0])); ++i) {
			if (command == allowed_edit[i]) {
				result = 1;
				break;
			}
		}
		break;
	case SOLVE:
		for(i = 0; i < (int)(sizeof (allowed_solve) / sizeof (allowed_solve[0])); ++i) {
			if (command == allowed_solve[i]) {
				result = 1;
				break;
			}
		}
		break;
	}
	return result;
}


/*
 * Verifies that x, y, and the set value (z) are valid values (between 0 and N = block_height*block_width);
 */
static int validate_values_for_set(char *x_str, char *y_str, char *z_str, int N) {
	int x = atoi(x_str);
	int y = atoi(y_str);
	int z = atoi(z_str);

	/*atoi() rounds values to int
	 *this is used to check input is not a fraction */
	double x_d = atof(x_str);
	double y_d = atof(y_str);
	double z_d = atof(z_str);

	if (x < 1 || x > N || (x - x_d) != 0) {
		return 0;
	}
	if (y < 1 || y > N || (y - y_d) != 0) {
		return 0;
	}
	if (z < 0 || z > N || (z - z_d) != 0) {
		return 0;
	}
	/*since atoi might return 0 on success if the string was 0*/
	if (z == 0 && strcmp(z_str, "0") != 0) {
		return 0;
	}
	return 1;
}


/*
 * Verifies that number of cells to be filled (x param)
 * and number of cells to be cleared (y param) are valid values (between 0 and E = empty cells);
 */
static int validate_values_for_generate(char *x_str, char *y_str, int E) {
	int x = atoi(x_str);
	int y = atoi(y_str);

	/*atoi() rounds values to int
	 *this is used to check input is not a fraction */
	double x_d = atof(x_str);
	double y_d = atof(y_str);

	if (x < 0 || x > E || (x - x_d) != 0) {
		return 0;
	}
	if (x == 0 && strcmp(x_str, "0") != 0) {
		return 0;
	}
	if (y < 0 || y > E || (y - y_d) != 0) {
		return 0;
	}
	if (y == 0 && strcmp(y_str, "0") != 0) {
		return 0;
	}
	return 1;
}

/*
 * Varifies that x and y are valid values (between 1 and N = block_height*block_width);
 */
static int validate_values_for_hint(char *x_str, char *y_str, int N) {
	int x = atoi(x_str);
	int y = atoi(y_str);

	/*atoi() rounds values to int
	 *this is used to check input is not a fraction */
	double x_d = atof(x_str);
	double y_d = atof(y_str);

	if (x < 1 || x > N || (x - x_d) != 0) {
		return 0;
	}
	if (y < 1 || y > N || (y - y_d) != 0) {
		return 0;
	}
	return 1;
}


static int save_file(Game *gp, char *filename) {
	FILE* file_ptr = fopen(filename,"w");
	if (file_ptr != NULL){
		writeToFile(gp, file_ptr);
		printf("Saved to: %s\n",filename);
		fclose(file_ptr);
	} else {
		/*couldn't open file*/
		printf("Error: File cannot be created or modified\n");
	}
	return 1;
}

/****************** INNER COMMAND IMPLEMENTATION ****************/
/*
 * Execute save command
 * Returns 1 on success, 0 on failure
 */
static int doSave(Game* gp, char *fileName){
	int solvable = 0;
	if (gp->mode == SOLVE) {
		save_file(gp, fileName);
	} else if (gp->mode == EDIT) {
		if (!isErroneousBoard(gp)) {
			solvable = isSolvable(gp);
			if (solvable == -1) {
				return -1;
			} else if (solvable) {
				save_file(gp, fileName);
			} else {
				/*board is not solvable*/
				printf("Error: board validation failed\n");
			}
		} else {
			/*there are bad values in the board*/
			printf( "Error: board contains erroneous values\n");
		}
	}
	return 1;
}

/*
 * Execute undo command
 * Returns 1 on success, 0 on failure
 */
static int doUndo(Game *game) {
	Action *action_to_undo = game->LatestAction;
	if (action_to_undo->type != INIT_A) {
		undoAction(game);
		game->LatestAction = action_to_undo->prev_action;

		if (UpdateErrors(game) == -1) {
			return -1;
		}

		printBoard(game, VALUE);
		if (action_to_undo->type == GENERATE_A) {
			printf("Undo Generate\n");
		} else {
			printUndoChanges(action_to_undo);
		}

	} else {
		printf("Error: no moves to undo\n");
	}
	return 1;
}

/*
 * Execute redo command
 * Returns 1 on success, 0 on failure
 */
static int doRedo(Game *game) {
	Action *action_to_redo;
	if (game->LatestAction != NULL) {
		action_to_redo = game->LatestAction->next_action;
		if (action_to_redo != NULL) {
			game->LatestAction = action_to_redo;

			redoAction(game);
			if (UpdateErrors(game) == -1) {
				return -1;
			}

			printBoard(game, VALUE);
			if (action_to_redo->type == GENERATE_A) {
				printf("Redo Generate\n");
			} else {
				printRedoChanges(action_to_redo);
			}

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
static int doReset(Game *game) {
	Action *action = game->LatestAction;

	while (action->type != INIT_A) {
		undoAction(game);
		game->LatestAction = game->LatestAction->prev_action;
		action = game->LatestAction;
	}

	freeActionsAfter(action);
	printf("Board reset\n");
	printBoard(game, VALUE);
	return 1;

}

/*
 * Moves the TEMP value to the VALUE of all nonzero tempValues in board.
 * This represents a multiple change move (such as autofill and generate).
 * Therefore, each updated value is saved as a change and added to the new action.
 * This action will become the new latest action.
 */
static int moveTempToValue(Game *game, actionType_e action_type) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int temp_value = 0;
	int val_before;
	Action *new_action = NULL;
	Change *changes = NULL;
	Change *new_change = NULL;

	for (y = 0; y < N; ++y) {
		for (x = 0; x < N; ++x) {
			temp_value = getNodeValByType(game, TEMP, x, y);
			if (temp_value != 0) {
				val_before = getNodeValByType(game, VALUE, x, y);
				setNodeValByType(game, VALUE, x , y, temp_value);

				new_change = initChange(x, y, val_before, temp_value, new_change);
				if (new_change == NULL) {
					printBoard(game, VALUE);
					return -1;
				}
				if (changes == NULL) {
					changes = new_change;
				}
			}
		}
	}
	if (changes != NULL) {
		new_action = (Action *) initAction(action_type, changes, game->LatestAction);
		game->LatestAction = new_action;
		if (new_action == NULL) {
			return -1;
		}
	}
	return 1;

}

/*
 * Returns the number of nonzero values in array.
 */
static int filled_cells(int *arr, int len){
	int i = 0;
	int filled_cells = 0;

	for(i = 0; i < len; ++i) {
		if (arr[i] != 0) {
			++filled_cells;
		}
	}
	return filled_cells;

}

/*
 * Returns the index(+1) of the first nonzero value in array.
 */
int get_first_value(int *arr, int len){
	int i = 0;

	for(i = 0; i < len; ++i) {
		if (arr[i] == 1) {
			return i + 1;
		}
	}
	return -1;
}

/*
 * Execute autofill command
 * Returns 1 on success, 0 on failure
 */
static int doAutofill(Game *game) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int *possible_vals_arr;
	int num_of_possible_vals = 0;
	int auto_value = 0;
	int value;

	if (isErroneousBoard(game) == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 0;
	}

	clearBoardByValType(game, TEMP);
	for (y = 0; y < N; ++y) {
		for (x = 0; x < N; ++x) {
			possible_vals_arr = calloc(N, sizeof(int));
			if (possible_vals_arr == NULL) {
				printf(CALLOC_ERROR);
				return -1;
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
	if (moveTempToValue(game, SET_A) == -1) {
		return -1;
	}
	if (UpdateErrors(game) == -1) {
		return -1;
	}
	printBoard(game, VALUE);
	return 1;
}

/*
 * Execute num_solutions command
 * Returns 1 on success, 0 on failure
 */
static int doGetNumofSols(Game *game) {
	unsigned long num_of_sols = 0;
	int error_code = 1;

	if (isErroneousBoard(game) == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 0;
	}

	num_of_sols = exhaustive_backtracking(game, &error_code);
	if (error_code == -1){
		return -1;
	}

	printf("Number of solutions: %lu\n", num_of_sols);

	if (num_of_sols == 1) {
		printf("This is a good board!\n");
	} else if (num_of_sols > 1) {
		printf("The puzzle has more than 1 solution, try to edit it further\n");
	}
	printBoard(game, VALUE);
	return 1;
}

static int doHint(Game *game, char *x, char *y) {
	int N = game->N;
	int x_val = 0, y_val = 0, hint_val = 0;
	int ILP_result = 0;

	x_val = atoi(x);
	y_val = atoi(y);
	if (validate_values_for_hint(x, y, N) != 1) {
		printf("Error: value not in range 1-%d\n", N);
		printBoard(game, VALUE);
		return 0;
	}

	x_val -= 1;
	y_val -= 1;

	if (isErroneousBoard(game) == 1) {
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
	} else if (ILP_result == -1) {
		return -1;
	} else {
		printf("Error: board is unsolvable\n");
		printBoard(game, VALUE);
		return 1;
	}

	printBoard(game, VALUE);
	return 0;

}

/*
 * Execute edit from file command.
 * Sets mode to edit and mark_errors to 1.
 * Returns 1 on success, 0 on failure.
 */
static int doEditFile(Game **game, char *fileName)  {
	FILE *f_pointer = fopen(fileName, "r");
	int mark_erros = (*game)->markErrors;
	int read_errors = 1;

	if (f_pointer == NULL) {
		printf("Error: File cannot be opened\n");
		return 0;
	}
	freeGame(*game);
	*game = readFromFile(f_pointer, &read_errors);
	fclose(f_pointer);

	/*check error code from read function*/
	if (*game == NULL || read_errors == -1) {
		return -1;
	} else if (*game == NULL || read_errors == 0) {
		return 0;
	}
	/*set mode and edit*/
	clearBoardByValType(*game, ISGIVEN);
	(*game)->mode = EDIT;
	(*game)->markErrors = mark_erros;
	if (UpdateErrors(*game) == -1) {
		return -1;
	}
	printBoard(*game, VALUE);
	return 1;
}

/*
 * Execute edit command.
 * Sets mode to edit and mark_errors to 1.
 * Returns 1 on success, 0 on failure.
 */
static int doEdit(Game **game)  {
	int mark_erros = (*game)->markErrors;

	freeGame(*game);
	*game = initGame(DEFAULT_BLOCK_HEIGHT,DEFAULT_BLOCK_WIDTH);
	if (*game == NULL) {
		return -1;
	}
	/*set mode and edit*/
	(*game)->mode = EDIT;
	(*game)->markErrors = mark_erros;
	if (UpdateErrors(*game) == -1) {
		return -1;
	}
	printBoard(*game, VALUE);
	return 1;
}

/*
 * Execute solve command
 * Returns 1 on success, 0 on failure
 */
static int doSolveFile(Game **game, char *fileName) {
	FILE *f_pointer = fopen(fileName, "r");
	int mark_erros = (*game)->markErrors;
	int read_errors = 1;

	if (f_pointer == NULL) {
		printf("Error: File doesn't exist or cannot be opened\n");
		return 0;
	}

	freeGame(*game);
	*game = readFromFile(f_pointer, &read_errors);
	fclose(f_pointer);

	/*check error code from read function*/
	if (*game == NULL || read_errors == -1) {
		return -1;
	} else if (*game == NULL || read_errors == 0) {
		return 0;
	}

	(*game)->markErrors = mark_erros;
	(*game)->mode = SOLVE;
	if (UpdateErrors(*game) == -1) {
		return -1;
	}
	printBoard(*game, VALUE);
	return 1;
}

/*
 * Execute mark_errors command
 * Returns 1 on success, 0 on failure
 */
static int doMarkErrors(Game *game, char *x) {
	int mark_errors_value = -1;
	double mark_errors_d;

	/*atoi() rounds values to int
	 *this is used to check input is not a fraction */
	mark_errors_value = atoi(x);
	mark_errors_d = atof(x);

	if (((mark_errors_value == 0 && strcmp(x, "0") == 0) || mark_errors_value == 1)
			&& (mark_errors_value - mark_errors_d) == 0) {
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
static int doValidate(Game *game) {
	int solvable = 0;

	if (isErroneousBoard(game) == 1) {
		printf("Error: board contains erroneous values\n");
		printBoard(game, VALUE);
		return 1;
	}
	solvable = isSolvable(game);
	if (solvable == 1) {
		printf("Validation passed: board is solvable\n");
	} else if (solvable == 0) {
		printf("Validation failed: board is unsolvable\n");
	} else if (solvable == -1){
		return -1;
	}
	printBoard(game, VALUE);
	return 0;
}


/*
 * Execute set command
 * Returns 1 on success, 0 on failure
 */
static int doSet(Game *game, char *x, char *y, char *z) {
	int x_val = 0, y_val = 0, z_val = 0;
	int N = game->blockHeight * game->blockWidth;
	Action *new_action; Change *new_change;
	int val_before;

	/*cast to int and validate values*/
	if (validate_values_for_set(x, y, z, N) != 1) {
		printf("Error: value not in range 0-%d\n", N);
		printBoard(game, VALUE);
		return 0;
	}
	x_val = atoi(x) - 1;
	y_val = atoi(y) - 1;
	z_val = atoi(z);

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

	/*update latest action only if value was changes*/
	if (val_before != z_val) {
		new_change = (Change *) initChange(x_val, y_val, val_before, z_val, NULL);
		if (new_change == NULL) {
			return -1;
		}
		new_action = (Action *) initAction(SET_A, new_change, game->LatestAction);
		if (new_action == NULL) {
			return -1;
		}
		game->LatestAction = new_action;
	}

	if (UpdateErrors(game) == -1) {
		return -1;
	}
	printBoard(game, VALUE);
	return 1;
}

static int doGenerate(Game *game, char *x, char *y) {
	int N = game->blockHeight * game->blockWidth;
	int filled_nodes = CountValuesInBoard(game);
	int E = (N*N) - filled_nodes;
	int x_val = 0, y_val = 0;
	int attempt, return_val = 0;

	if (validate_values_for_generate(x, y, E) != 1) {
		printf("Error: value not in range 0-%d\n", E);
		printBoard(game, VALUE);
		return 0;
	}
	x_val = atoi(x);
	y_val = atoi(y);

	if (filled_nodes != 0) {
		printf("Error: board is not empty\n");
		printBoard(game, VALUE);
		return 0;
	}
	for (attempt = 0; attempt < RETRY_ATTEMPTS_FOR_GENERATE; ++attempt) {
		clearBoardByValType(game, TEMP);
		if ((return_val = fill_nodes_random(game, TEMP, x_val)) == -1) {
			return -1;
		} else if (return_val != 1) {
			continue; }
		printBoard(game, TEMP);

		if ((return_val = fill_nodes_ILP(game, TEMP)) == -1) {
			return -1;
		} else if (return_val != GRB_OPTIMAL){
			continue; }
		printBoard(game, TEMP);

		if ((return_val = clear_nodes(game, TEMP, (N - y_val))) == -1) {
			return -1;
		} else if (return_val != 1) {
			continue; }
		printBoard(game, TEMP);

		if ((return_val = moveTempToValue(game, GENERATE_A)) == -1){
			return -1;;
		} else if (return_val != 1) {
			continue; }

		printBoard(game, VALUE);
		return 1;
	}
	printf("Error: puzzle generator failed\n");
	printBoard(game, VALUE);
	return 0;

}


/****************** OUTER INTERFACE FUNCTION ****************/
/*
 * get command from user - returns the compatible command_e enum,
 * and sets x_ptr, y_ptr and z_ptr to command parameters
 *
 * returns -1 on system function failure
 *
 */
command_e getCommand(mode_e mode, char *x_p, char *y_p, char *z_p){
	char str[MAX_SIZE] = {0};
	int valid = 0;
	int parsed;
	int valid_command = 0;
	command_e command = 0;

	 /*
	 * get command string, ignore \n
	 */
	while (valid == 0) {
		printf("Enter your command:\n");
		if (fgets(str, MAX_SIZE, stdin) == NULL){
			command = exit_game;
			break;
		}

		while ((strcmp(str,"\n") == 0)  || (strcmp(str,"\r\n") == 0)) {
			printf("Enter your command:\n");
			if (fgets(str, MAX_SIZE, stdin) == NULL){
				return exit_game;

			}
		}

		if ((parsed = parse(str, &command, x_p, y_p, z_p)) == 0) {
			printf("ERROR: invalid command\n");
		} else if (parsed == 1) {
			valid_command = validateCommandMode(command, mode);
			if (valid_command == 1){
				valid = 1;
			} else {
				printf("ERROR: invalid command\n");
			}
		}
	}
	return command;
}

/*
 * Execute the do function for the command, and returns same value as do function.
 */
int executeCommand(Game **game_p, command_e command, char *x, char *y, char *z) {
	Game *game = *game_p;

	switch(command){
	case print_board:
		printBoard(game, VALUE);
		return 1;
	case validate:
		return doValidate(game);
	case undo:
		return doUndo(game);
	case redo:
		return doRedo(game);
	case num_solutions:
		return doGetNumofSols(game);
	case autofill:
		return doAutofill(game);
	case reset:
		return doReset(game);
	case mark_errors:
		return doMarkErrors(game, x);
	case save:
		return doSave(game, x);
	case generate:
		return doGenerate(game, x, y);
	case hint:
		return doHint(game, x, y);
	case set:
		return doSet(game, x, y, z);
	case solve:
		return doSolveFile(game_p, x);
	case edit:
		return doEditFile(game_p, x);
	case edit_default:
		return doEdit(game_p);
	default:
		return -1;
	}
	return -1;
}

