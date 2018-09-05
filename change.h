/*
 * change.h
 *
 *  Created on: Sep 5, 2018
 *      Author: Dana Arad
 */

#ifndef CHANGE_H_
#define CHANGE_H_
#include "Game_structs.h"

Change *initChange(int x, int y, int val_before, int val_after, Change *prev);
void freeChanges(Change *change);
int printChange(command_e command, actionType_e actionType, Change change);

#endif /* CHANGE_H_ */
