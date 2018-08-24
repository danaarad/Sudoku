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
int doHint(int x, int y);
int doSave(char *fileName, mode_e mode);
int doEdit();
int doEditFile(char *fileName);
int doSolveFile(char *fileName);
int doUndo();
int doRedo();
int doMarkErrors();
int doValidate();
int doSet(int x, int y, int z);
int doGenerate(int x, int y);

#endif /* COMMANDS_H_ */
