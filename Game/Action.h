/*
 * Action.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "Game_structs.h"

typedef struct Action {
	int x;
	int y;
	Node* node_before_cahnge;
	Node* node_after_cahnge;
	struct Action* prev_action;
	struct Action* next_action;
	int is_prev_connected;
	int is_next_connected;
}Action;

Action *Latest_Action;

int getX(Action action);
int setX(Action action, int x);

int getY(Action action);
int setY(Action action, int y);

Node* getNodeBeforeChange(Action action);
int setNodeBeforeChange(Action action, Node* nodeBeforeChange);

Node* getNodeAfterChange(Action action);
int setNodeAfterChange(Action action, Node* nodeAfterChange);

Action* getPrevAction(Action action);
int setPrevAction(Action action, Action prev_action);

Action* getNextAction(Action action);
int setNextAction(Action action, Action prev_action);

int getIsPrevConnected(Action action);
int setIsPrevConnected(Action action, int isit_connected);

int getIsNextConnected(Action action);
int setIsNextConnected(Action action, int isit_connected);

Action* getLastAction();
int setLastAction(Action latest_action);

#endif /* ACTION_H_ */
