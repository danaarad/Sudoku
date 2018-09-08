/*
 * commands.h
 *
 *  Created on:
 *      Author: yael sapir
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_
#include "Game_structs.h"

command_e getCommand(mode_e mode, char *x_p, char *y_p, char *z_p);
int executeCommand(Game **game_p, command_e command, char *x, char *y, char *z);

#endif /* COMMANDS_H_ */

