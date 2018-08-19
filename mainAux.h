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
int executeCommand(mode_e mode, char *command, int *x, int *y, int *z);
void printBoard(Game* gp, mode_e mode, valType_e valType, int markErrorsOn, int toFileModeOn, FILE* file_ptr);



#endif /* MAINAUX_H_ */
