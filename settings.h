/*
 * settings.h
 *
 *  Created on: Aug 10, 2018
 *      Author: Dana Arad
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define MAX_COMMAND_SIZE 256
#define MAX_SIZE 1024

#include <stdio.h>

typedef enum mode {
	INIT,
	SOLVE,
	EDIT
} mode_e;

typedef enum command {
	print_board, validate,
	undo, redo,
	num_solutions, autofill,
	reset, exit,
	mark_errors, save,
	generate, hint,
	set, solve, edit
} command_e;


void pprint(char *str){
	printf(str);
	fflush(stdout);
}

#endif /* SETTINGS_H_ */
