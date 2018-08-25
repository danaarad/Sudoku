#include "Game_structs.h"
#include "settings.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const static struct {
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

command_e strToCommandEnum (char *str) {
	int j;
    for (j = 0;  j < sizeof (conversion) / sizeof (conversion[0]);  ++j)
    	if (!strcmp (str, conversion[j].str)) {
    		return conversion[j].command;
    	}
    return not_found;
}

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
		if (command_enum == generate ||
				command_enum == hint ||
				command_enum == set) {
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


