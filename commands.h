/*
 * commands.h
 *
 * Contains:
 * getCommand - receives and parses the command from the user.
 * The respective command_e enum is returnd, and x, y, z values are placed in the
 * given pointers
 *
 * executeCommand - execute the command implementation as described in the project
 * documents. this command uses inner static functions which implement each command seperatly
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_
#include "Game_structs.h"

#define RETRY_ATTEMPTS_FOR_GENERATE 1000

command_e getCommand(mode_e mode, char *x_p, char *y_p, char *z_p);
int executeCommand(Game **game_p, command_e command, char *x, char *y, char *z);

#endif /* COMMANDS_H_ */

