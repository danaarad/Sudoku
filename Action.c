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

/*
 * Return the first change of the action which
 * is also the head of the change list (since changes are saved as a linked list).
 */
Change *getChangeHead(Action *action){
	return action->changes;
}

/*
 * Sets the given change to head of the actions change list.
 * the function also frees all changes of the action if there are any.
 * This should not happen, however this is a safety measure to prevent
 * memory leaks.
 */
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

/*
 * Sets the second action as the next action of the first action,
 * and sets the first action as the previous action for the second one.
 * Any of the action pointers given to this function can be NULL.
 * Returns 1 on success, 0 on failure.
 */
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

/*Recursively frees all action before the given action (not included)*/
void freeActionsBefore(Action *action){
	Action *prev = action->prev_action;
	if (prev != NULL){
		freeActionsBefore(prev);
		freeChanges(prev->changes);
		free(prev);
	}
}

/*Recursively frees all action after the given action (not included)*/
void freeActionsAfter(Action *action){
	Action *next = action->next_action;
	if (next != NULL){
		freeActionsAfter(next);
		freeChanges(next->changes);
		free(next);
	}
}

/*
 * Frees a single action.
 * Assumes before and after are free.
 */
void freeSingleAction(Action *action){
	freeChanges(action->changes);
	free(action);
}

/*
 * Returns a pointer to a new allocated action with given paramaters.
 */
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
/*
 * Undo the latest action change by change.
 * Every change is undone by changing the value of node x,y from val after to val before.
 * The function returns the number of changes that were undone.
 */
int undoAction(Game *gp, int print){
	int x = 0, y = 0, val_before = 0, numOfUndone = 0;
	Action *action = gp->LatestAction;
	Change *curchange = action->changes;
	actionType_e actionType = action->type ;

	while(curchange){
		x = curchange->x; y = curchange->y;
		val_before = curchange->val_before;
		setNodeValByType(gp, VALUE, x, y, val_before);
		numOfUndone += 1;
		if (print == 1) {
			printChange(undo, actionType, curchange);
		}
		curchange = curchange->next;
	}
	return numOfUndone;
}

/*
 * Redo the latest action change by change.
 * Every change is redone by changing the value of node x,y from val before to val after.
 * The function returns the number of changes that were redone.
 */
int redoAction(Game *gp, int print){
	int x = 0, y = 0, val_after = 0, numOfUndone = 0;
	Action *action = gp->LatestAction;
	Change *curchange = action->changes;
	actionType_e actionType = action->type ;

	while(curchange){
		x = curchange->x; y = curchange->y;
		val_after = curchange->val_after;
		setNodeValByType(gp, VALUE, x, y, val_after);
		numOfUndone += 1;
		if (print == 1) {
			printChange(redo, actionType, curchange);
		}
		curchange = curchange->next;
	}
	return numOfUndone;
}

