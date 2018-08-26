/*
 * Action.c
 *
 *  Created on: 25 ���� 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include "Game_structs.h"

Action* initAction(){
	return (Action*)calloc(1,sizeof(Action));
}

int getActionX(Action *action){
	return action->x;
}
int setActionX(Action* action, int x){
	action->x = x;
	return action->x == x;
}

int getActionY(Action *action){
	return action->y;
}
int setActionY(Action *action, int y){
	action->y = y;
	return action->y == y;
}

int setActionXY(Action *action, int x, int y){
	int xok = setActionX(action,x);
	int yok = setActionY(action,y);
	return xok & yok;
}

Node* getNodeBeforeChange(Action *action){
	return action->node_before_change;
}
int setNodeBeforeChange(Action *action, Node* nodeBeforeChange){
	action->node_before_change = nodeBeforeChange;
	return action->node_before_change == nodeBeforeChange;
}

Node* getNodeAfterChange(Action *action){
	return action->node_after_change;
}
int setNodeAfterChange(Action *action, Node* nodeAfterChange){
	action->node_after_change = nodeAfterChange;
	return action->node_after_change == nodeAfterChange;
}

Action* getPrevAction(Action *action){
	return action->prev_action;
}
int setPrevAction(Action *action, Action *prev_action){
	int isprev, isnext;
	action->prev_action = prev_action;
	prev_action->next_action = action;
	isprev = (action->prev_action == prev_action);
	isnext = (prev_action->next_action == action);
	return isprev & isnext;

}

Action* getNextAction(Action *action){
	return action->next_action;
}

int setNextAction(Action *action, Action *next_action){
	int isprev, isnext;
	action->next_action = next_action;
	next_action->prev_action = action;
	isnext = (action->next_action == next_action);
	isprev = (next_action->prev_action == action);
	return isprev & isnext;
}

int getIsPrevConnected(Action *action){
	return action->is_prev_connected;
}
int setIsPrevConnected(Action *action, int isit_connected){
	int isprev, isnext;
	action->is_prev_connected = isit_connected;
	action->prev_action->is_next_connected = isit_connected;
	isprev = (action->is_prev_connected == isit_connected);
	isnext = (action->prev_action->is_next_connected == isit_connected);
	return isprev & isnext;
}

int getIsNextConnected(Action *action){
	return action->is_next_connected;
}
int setIsNextConnected(Action *action, int isit_connected){
	int isprev, isnext;
	action->is_next_connected = isit_connected;
	action->next_action->is_prev_connected = isit_connected;
	isnext = (action->is_next_connected == isit_connected);
	isprev = (action->next_action->is_prev_connected == isit_connected);
	return isprev & isnext;
}

void freeActionsBefore(Action *action){
	Action *prev = action->prev_action;
	if (prev != NULL){
		free(prev->node_before_change);
		free(prev->node_after_change);
		freeActionsBefore(prev);
		free(prev);
	}
	action->is_prev_connected = 0;
}
void freeActionsAfter(Action *action){
	Action *next = action->next_action;
	if (next != NULL){
		free(next->node_before_change);
		free(next->node_after_change);
		freeActionsAfter(next);
		free(next);
	}
	action->is_next_connected = 0;
}
/* expects before and after actions to be free*/
void freeSingleAction(Action *action){
	free(action->node_before_change);
	free(action->node_after_change);
	free(action);

}
