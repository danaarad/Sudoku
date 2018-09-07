/*
 * commands.h
 *
 *  Created on:
 *      Author: yael sapir
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_
#include "Game_structs.h"

int doReset(Game *game);
int doAutofill(Game *game);
int doGetNumofSols(Game *game);
int doHint(Game *game, char *x, char *y);
int doSave(Game *game, char *fileName);
int doEditFile(Game **game, char *fileName);
int doSolveFile(Game **game, char *fileName);
int doUndo(Game *game);
int doRedo(Game *game);
int doMarkErrors(Game *game, char *x);
int doValidate(Game *game);
int doSet(Game *game, char *x, char *y, char *z);
int doGenerate(Game *game, char *x, char *y);

#endif /* COMMANDS_H_ */
