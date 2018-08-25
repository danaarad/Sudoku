#include "mainAux.h"
#include "parser.h"
#include "printer.h"
#include "settings.h"
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int isWin() {
	return 0;
}

command_e getCommand(mode_e mode, int *x_p, int *y_p, int *z_p, char *fname_p){
	char *str = (char*) calloc(MAX_SIZE, sizeof(char));
	int valid = 0;
	int parsed;
	command_e command = 0;

	if (str == NULL) {
		printf(CALLOC_ERROR);
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
			if (validateCommandMode(command, mode) == 1){
				valid = 1;
			}
		}
	}
	free(str);
	return command;
}

int validateCommandMode(command_e command, mode_e mode) {
	command_e allowed_init[] = {solve, edit, edit_default, exit_game};
	command_e allowed_edit[] = {solve, edit, edit_default, print_board, set,
			validate, generate, undo, redo, save, num_solutions, reset, exit_game};
	command_e allowed_solve[] = {solve, edit, edit_default, mark_errors, print_board,
			set, validate, save, undo, redo, hint, num_solutions, autofill, reset, exit_game};
	int i = 0;

	switch(mode){
	case INIT:
		printf("INIT");
		for(i = 0; i < sizeof (allowed_init) / sizeof (allowed_init[0]); ++i) {
			if (command == allowed_init[i]) {
				return 1;
			}
		}
		return 0;
	case EDIT:
		printf("EDIT");
		for(i = 0; i < sizeof (allowed_edit) / sizeof (allowed_edit[0]); ++i) {
			if (command == allowed_edit[i]) {
				return 1;
			}
		}
		return 0;
	case SOLVE:
		printf("SOLVE");
		for(i = 0; i < sizeof (allowed_solve) / sizeof (allowed_solve[0]); ++i) {
			if (command == allowed_solve[i]) {
				return 1;
			}
		}
		return 0;
	}
}

int executeCommand(Game *game, command_e command, int x, int y, int z, char *fname) {
	mode_e mode = game->mode;

	switch(command){
	case print_board:
		printBoard(game, VALUE);
		return 1;
	case validate:
		return doValidate();
	case undo:
		return doUndo();
	case redo:
		return doRedo();
	case num_solutions:
		return doGetNumofSols();
	case autofill:
		return doAutofill();
	case reset:
		return doReset();
	case exit_game:
		return doExit();
	case mark_errors:
		return doMarkErrors(x);
	case save:
		return doSave(fname, game->mode);
	case generate:
		return doGenerate(x, y);
	case hint:
		return doHint(x, y);
	case set:
		return doSet(x, y, z);
	case solve:
		return doSolveFile(game, fname);
	case edit:
		return doEditFile(fname);
	case edit_default:
		printBoard(game, VALUE);
		return 1;
	case not_found:
		return -1;
	}
	return -1;
}

