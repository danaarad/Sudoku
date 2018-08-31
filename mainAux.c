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


int isWin(Game *game) {
	int N = game->blockHeight * game->blockWidth;

	if (game->filledNodes == (N * N)){
		if (game->mode == SOLVE) {
			if (game->isErrornous == 1) {
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

command_e getCommand(mode_e mode, char *x_p, char *y_p, char *z_p){
	char *str = (char*) calloc(MAX_SIZE, sizeof(char));
	int valid = 0;
	int parsed;
	int valid_command = 0;
	command_e command = 0;

	fflush(stdout);
	if (str == NULL) {
		printf(CALLOC_ERROR);
		fflush(stdout);
		return -1;
	}
	 /*
	 * get command string, ignore \n
	 */
	while (valid == 0) {
		printf("Enter your command:\n");
		fflush(stdout);

		if (fgets(str, MAX_SIZE, stdin) == NULL){
			strcpy(str, "exit");
			break;
		}

		while ((strcmp(str,"\n") == 0)  || (strcmp(str,"\r\n") == 0)) {
			printf("Enter your command:\n");
			fflush(stdout);
			if (fgets(str, MAX_SIZE, stdin) == NULL){
				strcpy(str, "exit");
				valid = 1;
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
	fflush(stdout);
	return command;
}

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
		for(i = 0; i < (sizeof (allowed_init) / sizeof (allowed_init[0])); ++i) {
			fflush(stdout);
			if (command == allowed_init[i]) {
				result = 1;
				break;
			}
		}
		break;
	case EDIT:
		for(i = 0; i < sizeof (allowed_edit) / sizeof (allowed_edit[0]); ++i) {
			if (command == allowed_edit[i]) {
				result = 1;
				break;
			}
		}
		break;
	case SOLVE:
		for(i = 0; i < sizeof (allowed_solve) / sizeof (allowed_solve[0]); ++i) {
			if (command == allowed_solve[i]) {
				result = 1;
				break;
			}
		}
		break;
	}
	return result;
}

int executeCommand(Game *game, command_e command, char *x, char *y, char *z) {
	mode_e mode = game->mode;

	switch(command){
	case print_board:
		printBoard(game, VALUE);
		return 1;
	case validate:
		return doValidate(game);
	case undo:
		return doUndo();
	case redo:
		return doRedo();
	case num_solutions:
		return doGetNumofSols(game);
	case autofill:
		return doAutofill(game);
	case reset:
		return doReset();
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
		return doSolveFile(game, x);
	case edit:
		return doEditFile(game, x);
	case edit_default:
		printBoard(game, VALUE);
		return 1;
	case not_found:
		return -1;
	}
	return -1;
}

