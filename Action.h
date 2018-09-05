/*
 * Action.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "Game_structs.h"

Change *getChangeHead(Action *action);
int setChangeHead(Action *action, Change *head);

int getActionType(Action *action);
int setActionType(Action *action, actionType_e aType);

Action* getPrevAction(Action *action);
Action* getNextAction(Action *action);
int setNextAction(Action *action, Action *next_action);

void freeActionsBefore(Action *action);
void freeActionsAfter(Action *action);
void freeSingleAction(Action *action);

Action* initAction(actionType_e actionType,Change* changes, Action* prev_action);

int undoAction(Game *gp, int print);
int redoAction(Game *gp, int print);

#endif /* ACTION_H_ */
