#include "mainAux.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



/*
 * performs parsing of str <"command x y z"> to its tokens
 * placing tokens in pointer location, respectivly
 *
 * returns 1 if success, 0 else.
 */
int parse(char str[], char *command, int *x_pointer, int *y_pointer, int *z_pointer, char *fname_pointer) {
	const char delim[2] = " ";
	char *token = {0};
	int i = 0;
	char *commands_with_zero_params[] = {"print_board",
			"validate", "undo", "redo", "num_solutions",
			"autofill", "reset", "exit"};
	int len_commands_with_zero_params = 8;

	char *commands_with_int_params[] = {"mark_errors",
			"save", "generate", "hint", "set"};
	int len_commands_with_int_params = 6;

	char *commands_with_str_params[] = {"solve", "edit"};
	int len_commands_with_str_params = 2;


	token = strtok(str, delim);
	if (sscanf(token, "%s", command) != 1) {
		return -1;
	}

	for(i = 0; i < len_commands_with_zero_params; i++){
		if (strcmp(command, commands_with_zero_params[i]) == 0) {
			return 1;
		}
	}

	for(i = 0; i < len_commands_with_str_params; i++){
		if (strcmp(command, commands_with_str_params[i]) == 0) {
			token = strtok(NULL, delim);
			if ((token == NULL) ||(sscanf(token, "%s", fname_pointer) != 1)) {
				if (strcmp(command, "edit") == 0) {
					strcpy(command, "edit_default");
					return 1;
				}
				return 0;
			}
			return 1;
		}
	}

	for(i = 0; i < len_commands_with_int_params; i++){
		if (strcmp(command, commands_with_int_params[i]) == 0) {
			token = strtok(NULL, delim);
			if ((token == NULL) ||(sscanf(token, "%d", x_pointer) != 1)) {
				return 0;
			}
			if ((strcmp(command, "generate") == 0) ||
					(strcmp(command, "hint") == 0) ||
					(strcmp(command, "set") == 0)) {
				token = strtok(NULL, delim);
				if ((token == NULL) || (sscanf(token, "%d", y_pointer) != 1)) {
					return 0;
				}
			}
			if (strcmp(command, "set") == 0) {
				token = strtok(NULL, delim);
				if ((token == NULL) || (sscanf(token, "%d", z_pointer) != 1)) {
					return 0;
				}
			}
			return 1;
			}
		}
	return 0;
	}
