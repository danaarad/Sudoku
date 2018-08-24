/*
 * MainAux.h
 *
 *  Created on: May 8, 2018
 *      Author: Dana Arad
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "Game_structs.h"

int getCommand(mode_e mode, char *command, int *x, int *y, int *z, char *fname_p);
int executeCommand(mode_e mode, char *command, int *x, int *y, int *z, char *fname);

#endif /* MAINAUX_H_ */
