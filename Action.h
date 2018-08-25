/*
 * Action.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "Game_structs.h"


int getActionX(Action *action);
int setActionX(Action *action, int x);

int getActionY(Action *action);
int setActionY(Action *action, int y);

int setActionXY(Action *action, int x, int y);

Node* getNodeBeforeChange(Action *action);
int setNodeBeforeChange(Action *action, Node* nodeBeforeChange);

Node* getNodeAfterChange(Action *action);
int setNodeAfterChange(Action *action, Node* nodeAfterChange);

Action* getPrevAction(Action *action);
int setPrevAction(Action *action, Action *prev_action);

Action* getNextAction(Action *action);
int setNextAction(Action *action, Action *next_action);

int getIsPrevConnected(Action *action);
int setIsPrevConnected(Action *action, int isit_connected);

int getIsNextConnected(Action *action);
int setIsNextConnected(Action *action, int isit_connected);


#endif /* ACTION_H_ */
