/*
 * commands.h
 *
 *  Created on: 11 баев 2018
 *      Author: yael sapir
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_
#include "Game_structs.h"

int doExit();
int doReset();
int doAutofill();
int doGetNumofSols();
int doHint(char *x, char *y);
int doSave(char *fileName, mode_e mode);
int doEditFile(Game *game, char *fileName);
int doSolveFile(Game *game, char *fileName);
int doUndo();
int doRedo();
int doMarkErrors(Game *game, char *x);
int doValidate();
int doSet(Game *game, char *x, char *y, char *z);
int doGenerate(char *x, char *y);

#endif /* COMMANDS_H_ */
