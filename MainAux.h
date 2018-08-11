/*
 * MainAux.h
 *
 *  Created on: May 8, 2018
 *      Author: Dana Arad
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_

int getCommand(mode_e mode, char *command, int *x, int *y, int *z);
int executeCommand(mode_e mode, char *command, int *x, int *y, int *z);
void printBoard(FILE* file_ptr, int markErrorsOn, mode_e mode, int toFileModeOn);



#endif /* MAINAUX_H_ */
