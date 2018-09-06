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
			if (game->isErrornous == 0) {
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
			strcpy(str, "exit\n");
			break;
		}

		while ((strcmp(str,"\n") == 0)  || (strcmp(str,"\r\n") == 0)) {
			printf("Enter your command:\n");
			fflush(stdout);
			if (fgets(str, MAX_SIZE, stdin) == NULL){
				strcpy(str, "exit\n");
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
		for(i = 0; i < (int)(sizeof (allowed_init) / sizeof (allowed_init[0])); ++i) {
			fflush(stdout);
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

int executeCommand(Game *game, command_e command, char *x, char *y, char *z) {
	int res = 0;

	switch(command){
	case print_board:
		printBoard(game, VALUE);
		return 1;
	case validate:
		printf("starting validate\n");
		res = doValidate(game);
		printf("finished validate\n");
		fflush(stdout);
		return res;
	case undo:
		printf("starting undo\n");
		res = doUndo(game);
		printf("finished undo\n");
		fflush(stdout);
		return res;
	case redo:
		printf("starting redo\n");
		res = doRedo(game);
		fflush(stdout);
		printf("finished redo\n");
		return res;
	case num_solutions:
		res = doGetNumofSols(game);
		return res;
	case autofill:
		res = doAutofill(game);
		return res;
	case reset:
		printf("starting reset\n");
		res = doReset(game);
		printf("finished reset\n");
		fflush(stdout);
		return res;
	case mark_errors:
		res = doMarkErrors(game, x);
		return res;
	case save:
		printf("starting save\n");
		res = doSave(game, x);
		printf("finished save\n");
		fflush(stdout);
		return res;
	case generate:
		printf("starting generate\n");
		res = doGenerate(game, x, y);
		printf("finished generate\n");
		fflush(stdout);
		return res;
	case hint:
		printf("starting hint\n");
		res = doHint(game, x, y);
		printf("finished hint\n");
		fflush(stdout);
		return res;
	case set:
		res = doSet(game, x, y, z);
		return res;
	case solve:
		res = doSolveFile(game, x);
		return res;
	case edit:
		res = doEditFile(game, x);
		return res;
	case edit_default:
		game->mode = EDIT;
		printBoard(game, VALUE);
		return 1;
	case exit_game:
	case not_found:
		return -1;
	}
	return -1;
}

