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
void printBoard(FILE* file_ptr);



#endif /* MAINAUX_H_ */
