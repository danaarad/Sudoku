/*
 * MainAux.h
 *
 *  Created on: May 8, 2018
 *      Author: Dana Arad
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "Game_structs.h"

int isWin();
command_e getCommand(mode_e mode, char *x_p, char *y_p, char *z_p);
int executeCommand(Game **game, command_e command, char *x, char *y, char *z);
int validateCommandMode(command_e command, mode_e mode);
#endif /* MAINAUX_H_ */
