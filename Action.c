/*
 * Action.c
 *
 *  Created on: 25 баев 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include "Game_structs.h"
#include "Node.h"
#include "change.h"
#include "settings.h"
#include "Action.h"

Change *getChangeHead(Action *action){
	return action->changes;
}

int setChangeHead(Action *action, Change *head){
	freeChanges(action->changes);
	action->changes = head;
	return (action->changes == head);
}

int getActionType(Action *action){
	return action->type;
}

int setActionType(Action *action, actionType_e aType){
	action->type = aType;
	return action->type == aType;
}

Action* getPrevAction(Action *action){
	return action->prev_action;
}

Action* getNextAction(Action *action){
	return action->next_action;
}

int setNextAction(Action *action, Action *next_action){
	int isprev = 1, isnext = 1;

	if(action){
		freeActionsAfter(action);
		action->next_action = next_action;
		isnext = (action->next_action == next_action);
	}
	if(next_action){
		freeActionsBefore(next_action);
		next_action->prev_action = action;
		isprev = (next_action->prev_action == action);
	}
	return isprev && isnext;
}

void freeActionsBefore(Action *action){
	Action *prev = action->prev_action;
	if (prev != NULL){
		freeActionsBefore(prev);
		freeChanges(prev->changes);
		free(prev);
	}
}
void freeActionsAfter(Action *action){
	Action *next = action->next_action;
	if (next != NULL){
		freeActionsAfter(next);
		freeChanges(next->changes);
		free(next);
	}
}

/*assumes before and after are free*/
void freeSingleAction(Action *action){
	freeChanges(action->changes);
	free(action);
}

Action* initAction(actionType_e actionType,Change* changes, Action* prev_action){
	Action *newAction = (Action*)calloc(1,sizeof(Action));
	int atok, cok, paok;
	if(newAction){
		atok = setActionType(newAction, actionType);
		cok = setChangeHead(newAction,changes);
		paok = setNextAction(prev_action,newAction);

		if(!(atok && cok && paok)){
			printf(INIT_ERROR);
			return NULL;
		}
	}else{
		printf(CALLOC_ERROR);
	}
	return newAction;
}

int undoAction(Game *gp, int print){
	int x, y, val_before, numOfUndone;
	Action *action = gp->LatestAction;
	Change *curchange = action->changes;
	actionType_e actionType = action->type ;

	while(curchange){
		x = curchange->x; y = curchange->y;
		val_before = curchange->val_before;
		numOfUndone += setNodeValByType(gp, VALUE, x, y, val_before);
		if (print == 1) {
			printChange(undo, actionType ,curchange);
		}
		curchange = curchange->next;
	}
	return numOfUndone;
}

int redoAction(Game *gp, int print){
	int x, y, val_after, numOfUndone;
	Action *action = gp->LatestAction;
	Change *curchange = action->changes;
	actionType_e actionType = action->type ;

	while(curchange){
		x = curchange->x; y = curchange->y;
		val_after = curchange->val_after;
		numOfUndone += setNodeValByType(gp, VALUE, x, y, val_after);
		if (print == 1) {
			printChange(redo, actionType ,curchange);
		}
		curchange = curchange->next;
	}
	return numOfUndone;
}

