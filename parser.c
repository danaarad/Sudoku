/*
 *
 * parser.c
 *
 * Parses string into a command_e enum and parameters,
 * using a conversion function and struct.
 *
 * Note that parameters are not validated in this module
 *
 *
 */


#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "settings.h"


static const struct {
    command_e command;
    const char *str;
} conversion [] = {
		{print_board, "print_board"},
		{validate, "validate"},
		{undo, "undo"},
		{redo, "redo"},
		{num_solutions, "num_solutions"},
		{autofill, "autofill"},
		{reset, "reset"},
		{exit_game, "exit"},
		{mark_errors, "mark_errors"},
		{save, "save"},
		{generate, "generate"},
		{hint, "hint"},
		{set, "set"},
		{solve, "solve"},
		{edit, "edit"}
};

/*
 * converts str into the corresponding command_e enum,
 * or not_found if not found.
 *
 * Uses the conversions struct defined above.
 */
command_e strToCommandEnum (char *str) {
	int j;
    for (j = 0;  j < (int)(sizeof (conversion) / sizeof (conversion[0]));  ++j)
    	if (!strcmp (str, conversion[j].str)) {
    		return conversion[j].command;
    	}
    return not_found;
}

/*
 * Parses str into a command_e enum and parameters
 * Argument values are places in corresponding pointers
 * Extra parameters are ignored
 *
 * Returns 1 if str contains a valid command and correct number of parameters
 * else 0.
 *
 * Note that parameters are not validated in this function.
 */
int parse(char str[], command_e *command_pointer, char *x_pointer, char *y_pointer, char *z_pointer) {
	const char delim[2] = " ";
	char *token = {0};
	command_e command_enum;
	char command_str[MAX_COMMAND_SIZE];

	if ((int) strlen(str) > MAX_COMMAND_SIZE) {
			return 0;
	}

	token = strtok(str, delim);
	if (sscanf(token, "%s", command_str) != 1) {
		return -1;
	}

	command_enum = strToCommandEnum(command_str);
	switch(command_enum) {
	case not_found:
		*command_pointer = command_enum;
		return 0;
	/*zero argument commands:*/
	case print_board:
	case validate:
	case undo:
	case redo:
	case num_solutions:
	case autofill:
	case reset:
	case exit_game:
		*command_pointer = command_enum;
		return 1;
	/*one or more argument commands*/
	case solve:
	case edit:
	case save:
	case mark_errors:
	case generate:
	case hint:
	case set:
		token = strtok(NULL, delim);
		if ((token == NULL) ||(sscanf(token, "%s", x_pointer) != 1)) {
			if (command_enum == edit) {
				command_enum = edit_default;
				*command_pointer = command_enum;
				return 1;
			}
			return 0;
		}
		if (command_enum == generate || command_enum == hint || command_enum == set) {
			token = strtok(NULL, delim);
			if ((token == NULL) || (sscanf(token, "%s", y_pointer) != 1)) {
				return 0;
			}
		}
		if (command_enum == set) {
			token = strtok(NULL, delim);
			if ((token == NULL) || (sscanf(token, "%s", z_pointer) != 1)) {
				return 0;
			}
		}
		*command_pointer = command_enum;
		return 1;
	default:
		command_enum = not_found;
		*command_pointer = command_enum;
		return 0;
	}

}


