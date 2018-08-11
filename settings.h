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

typedef enum mode {
	INIT,
	SOLVE,
	EDIT
} mode_e;

char *commands_with_zero_params[] = {"print_board",
		"validate", "undo", "redo", "num_solutions",
		"autofill", "reset", "exit"};
int len_commands_with_zero_params = 8;

char *commands_with_int_params[] = {"mark_errors",
		"save", "generate", "hint", "set"};
int len_commands_with_int_params = 6;

char *commands_with_str_params[] = {"solve", "edit"};
int len_commands_with_str_params = 2;

void pprint(char *str){
	printf(str);
	fflush(stdout);
}

#endif /* SETTINGS_H_ */
