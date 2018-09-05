/*
 * Action.c
 *
 *  Created on: 25 ���� 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include "Game_structs.h"
#include "Node.h"
#include "settings.h"
#include "Action.h"

int getActionType(Action *action){
	return action->type;
}

int setActionType(Action *action, actionType_e aType){
	action->type = aType;
	return action->type == aType;
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
	return xok && yok;
}

int getValBeforeChange(Action *action){
	return action->val_before_change;
}
int setValBeforeChange(Action *action, int valBeforeChange){
	action->val_before_change = valBeforeChange;
	return action->val_before_change == valBeforeChange;
}

int getValAfterChange(Action *action){
	return action->val_after_change;
}
int setValAfterChange(Action *action, int valAfterChange){
	action->val_after_change = valAfterChange;
	return action->val_after_change == valAfterChange;
}

Action* getPrevAction(Action *action){
	return action->prev_action;
}
int setPrevAction(Action *action, Action *prev_action, int isPrevConnected){
	int isprev, isnext;

	freeActionsBefore(action);
	action->prev_action = prev_action;
	action->is_prev_connected = isPrevConnected;
	isprev = (action->prev_action == prev_action);

	if(prev_action){
		freeActionsAfter(prev_action);
		prev_action->next_action = action;
		prev_action->is_next_connected = isPrevConnected;
		isnext = (prev_action->next_action == action);
	}
	else{
		action->is_prev_connected = 0;//there is no prev
		isnext = 1;
	}
	return isprev && isnext;

}

Action* getNextAction(Action *action){
	return action->next_action;
}

int setNextAction(Action *action, Action *next_action, int isNextConnected){
	int isprev = 0, isnext = 0;

	freeActionsAfter(action);
	action->next_action = next_action;
	action->is_next_connected = isNextConnected;
	isnext = (action->next_action == next_action);

	if(next_action){
		freeActionsBefore(next_action);
		next_action->prev_action = action;
		next_action->is_prev_connected = isNextConnected;
		isprev = (next_action->prev_action == action);
	}else{
		action->is_next_connected = 0;//there is no next
		isprev = 1;
	}

	return isprev && isnext;
}

int getIsPrevConnected(Action *action){
	return action->is_prev_connected;
}

int setIsPrevConnected(Action *action, int isit_connected){
	int isprev, isnext;

	if(!action->prev_action){
		return 0;//there is no prev;
	}
	action->is_prev_connected = isit_connected;
	action->prev_action->is_next_connected = isit_connected;
	isprev = (action->is_prev_connected == isit_connected);
	isnext = (action->prev_action->is_next_connected == isit_connected);
	return isprev && isnext;
}

int getIsNextConnected(Action *action){
	return action->is_next_connected;
}

int setIsNextConnected(Action *action, int isit_connected){
	int isprev, isnext;

	if(!action->next_action){
		return 0;//there is no next;
	}
	action->is_next_connected = isit_connected;
	action->next_action->is_prev_connected = isit_connected;
	isnext = (action->is_next_connected == isit_connected);
	isprev = (action->next_action->is_prev_connected == isit_connected);
	return isprev && isnext;
}

void freeActionsBefore(Action *action){
	Action *prev = action->prev_action;
	if (prev != NULL){
		freeActionsBefore(prev);
		free(prev);
	}
	action->is_prev_connected = 0;
}
void freeActionsAfter(Action *action){
	Action *next = action->next_action;
	if (next != NULL){
		freeActionsAfter(next);
		free(next);
	}
	action->is_next_connected = 0;
}

void freeSingleAction(Action *action){
	free(action);
}

Action* initAction(actionType_e actionType, int x, int y, int valBeforeChange, int valAfterChange, Action* prev_action, int is_prev_connected){
	Action *newAction = (Action*)calloc(1,sizeof(Action));
	int atok, xok, yok, nbok, naok, paok;
	if(newAction){
		atok = setActionType(newAction, actionType);
		xok = setActionX(newAction, x);
		yok = setActionY(newAction, y);
		nbok = setValBeforeChange(newAction,valBeforeChange);
		naok = setValAfterChange(newAction,valAfterChange);
		paok = setPrevAction(newAction, prev_action, is_prev_connected);
		if(!(atok && xok && yok && nbok && naok && paok)){
			printf(INIT_ERROR);
			return NULL;
		}
	}else{
		printf(CALLOC_ERROR);
	}
	return newAction;
}

