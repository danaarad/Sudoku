#include "mainAux.h"
#include "parser.h"
#include "printer.h"
#include "settings.h"
#include "commands.h"
#include "Game.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/*
 * Returns 1 if game board is solved successfully
 * 		   0 if board is erroneous of not full
 */
int isWin(Game *game) {
	int N = game->blockHeight * game->blockWidth;
	if (game->filledNodes == (N * N)){
		if (game->mode == SOLVE) {
			if (isErrornousBoard(game) == 0) {
				printf("Puzzle solved successfully\n");
				return 1;
			} else {
				printf("Puzzle solution erroneous\n");
				return 0;
			}
		}
	}

	return 0;
}


/*
 * get command from user - returns the compatible command_e enum,
 * and sets x_ptr, y_ptr and z_ptr to command parameters
 *
 * returns -1 on system function failure
 *
 */
command_e getCommand(mode_e mode, char *x_p, char *y_p, char *z_p){
	char *str = (char*) calloc(MAX_SIZE, sizeof(char));
	int valid = 0;
	int parsed;
	int valid_command = 0;
	command_e command = 0;

	if (str == NULL) {
		printf(CALLOC_ERROR);
		return -1;
	}
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
				free(str);
				return exit_game;

			}
		}

		if ((parsed = parse(str, &command, x_p, y_p, z_p)) == 0) {
			printf("ERROR: invalid command 111111\n");
		} else if (parsed == 1) {
			valid_command = validateCommandMode(command, mode);
			if (valid_command == 1){
				valid = 1;
			} else {
				printf("ERROR: invalid command 2222\n");
			}
		}
	}
	free(str);
	return command;
}

/*
 * Validates command is compatible with mode, according to project documents.
 * Return 1 if compatible, 0 otherwise
 */
int validateCommandMode(command_e command, mode_e mode) {
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
 * Execute the do function for the command, and returns same value as do function.
 */
int executeCommand(Game **game_p, command_e command, char *x, char *y, char *z) {
	int res = 0;
	Game *game = *game_p;

	switch(command){
	case print_board:
		printBoard(game, VALUE);
		return 1;
	case validate:
		res = doValidate(game);
		return res;
	case undo:
		res = doUndo(game);
		return res;
	case redo:
		res = doRedo(game);
		return res;
	case num_solutions:
		res = doGetNumofSols(game);
		return res;
	case autofill:
		res = doAutofill(game);
		return res;
	case reset:
		res = doReset(game);
		return res;
	case mark_errors:
		res = doMarkErrors(game, x);
		return res;
	case save:
		res = doSave(game, x);
		return res;
	case generate:
		res = doGenerate(game, x, y);
		return res;
	case hint:
		res = doHint(game, x, y);
		return res;
	case set:
		res = doSet(game, x, y, z);
		return res;
	case solve:
		res = doSolveFile(game_p, x);
		return res;
	case edit:
		res = doEditFile(game_p, x);
		return res;
	case edit_default:
		game->mode = EDIT;
		printBoard(game, VALUE);
		return 1;
	default:
		return -1;
	}
	return -1;
}

