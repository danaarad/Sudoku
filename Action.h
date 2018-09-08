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

Action* initAction(actionType_e actionType,Change* changes, Action* prev_action);

void undoAction(Game *gp, int print);
void redoAction(Game *gp, int print);

#endif /* ACTION_H_ */
