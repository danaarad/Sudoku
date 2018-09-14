/*
 * Action.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "Game_structs.h"

void freeActionsBefore(Action *action);
void freeActionsAfter(Action *action);
void freeSingleAction(Action *action);
void freeChanges(Change *change);

Action *initAction(actionType_e actionType,Change* changes, Action* prev_action);
Change *initChange(int x, int y, int val_before, int val_after, Change *prev);

void undoAction(Game *gp);
void redoAction(Game *gp);

void printUndoChanges(Action *action);
void printRedoChanges(Action *action);
void printChange(command_e command, actionType_e actionType, Change *change);


#endif /* ACTION_H_ */
