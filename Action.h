/*
 * Action.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "Game_structs.h"


int getActionType(Action *action);

int setActionType(Action *action, actionType_e aType);

int getActionX(Action *action);
int setActionX(Action* action, int x);

int getActionY(Action *action);
int setActionY(Action *action, int y);

int setActionXY(Action *action, int x, int y);

int getValBeforeChange(Action *action);
int setValBeforeChange(Action *action, int valBeforeChange);

int getValAfterChange(Action *action);
int setValAfterChange(Action *action, int valAfterChange);

Action* getPrevAction(Action *action);

Action* getNextAction(Action *action);

int setNextAction(Action *action, Action *next_action, int isNextConnected);

int getIsPrevConnected(Action *action);

int setIsPrevConnected(Action *action, int isit_connected);

int getIsNextConnected(Action *action);

int setIsNextConnected(Action *action, int isit_connected);

void freeActionsBefore(Action *action);
void freeActionsAfter(Action *action);
void freeSingleAction(Action *action);

Action* initAction(actionType_e actionType, int x, int y, int valBeforeChange, int valAfterChange, Action* prev_action, int is_prev_connected);


#endif /* ACTION_H_ */
