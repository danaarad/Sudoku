/*
 * MainAux.h
 *
 *  Created on: May 8, 2018
 *      Author: Dana Arad
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_

#include "Game.h"
#include "Node.h"
#include "settings.h"

int getCommand(mode_e mode, char *command, int *x, int *y, int *z, char *fname_p);
int parse(char str[], char *command, int *x_pointer, int *y_pointer, int *z_pointer, char *fname_pointer);
int executeCommand(mode_e mode, char *command, int *x, int *y, int *z, char *fname);
void printBoard(Game* gp, valType_e valType);



#endif /* MAINAUX_H_ */
