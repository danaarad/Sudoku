/*
 * Action.c
 *
 * Contains the Action and Changes interface
 * This interface contains init and free functions, and also redo / undo and print functions.
 *
 * This file contains:
 *  - Setters
 *  - Init functions
 *  - Free functions
 *  - Undo an Redo functions (outer interface)
 *  - Print functions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "Action.h"
#include "Game.h"

/********************* SETTERS *********************/

/*
 * Sets the given change to head of the actions change list.
 * the function also frees all changes of the action if there are any.
 * This should not happen, however this is a safety measure to prevent
 * memory leaks.
 */
static void setChangeHead(Action *action, Change *head) {
	freeChanges(action->changes);
	action->changes = head;
}


static void setActionType(Action *action, actionType_e aType) {
	action->type = aType;
}

/*
 * Sets the second action as the next action of the first action,
 * and sets the first action as the previous action for the second one.
 * Any of the action pointers given to this function can be NULL.
 */
static void setNextAction(Action *action, Action *next_action) {

	if(action){
		freeActionsAfter(action);
		action->next_action = next_action;
	}
	if(next_action){
		freeActionsBefore(next_action);
		next_action->prev_action = action;
	}
}


/********************* INIT FUNCTIONS *********************/

/*
 * Creates a Change object and adds it after previous Change (prev).
 * This change should be set after the last change in the change chain.
 */
Change *initChange(int x, int y, int val_before, int val_after, Change *prev) {
	Change *newChange = (Change*)calloc(1,sizeof(Change));

	if (newChange == NULL) {
		printf(CALLOC_ERROR);
		return NULL;
	}
	newChange->x = x;
	newChange->y = y;
	newChange->val_before = val_before;
	newChange->val_after = val_after;
	newChange->next = NULL;
	if (prev != NULL) {
		prev->next = newChange;
	}

	return newChange;
}

/*
 * Returns a pointer to a new allocated action with given paramaters.
 */
Action* initAction(actionType_e actionType,Change* changes, Action* prev_action) {
	Action *newAction = (Action*)calloc(1,sizeof(Action));
	if (newAction) {
		setActionType(newAction, actionType);
		setChangeHead(newAction,changes);
		setNextAction(prev_action,newAction);
	} else {
		printf(CALLOC_ERROR);
	}
	return newAction;
}

/********************* FREE FUNCTIONS *********************/

/*
 * Recursive free of changes in action.
 */
void freeChanges(Change *change) {
	Change *next;
	if (change != NULL) {
		next = change->next;
		freeChanges(next);
		free(change);
	}
}

/*
 * Recursively frees all actions before the given action (not included)
 */
void freeActionsBefore(Action *action) {
	Action *prev = action->prev_action;
	if (prev != NULL){
		freeActionsBefore(prev);
		freeChanges(prev->changes);
		free(prev);
	}
	action->prev_action = NULL;
}

/*
 * Recursively frees all actions after the given action (not included)
 */
void freeActionsAfter(Action *action) {
	Action *next = action->next_action;
	if (next != NULL){
		freeActionsAfter(next);
		freeChanges(next->changes);
		free(next);
	}
	action->next_action = NULL;
}

/*
 * Frees a single action.
 * Assumes before and after are free.
 */
void freeSingleAction(Action *action) {
	freeChanges(action->changes);
	free(action);
}


/********************* UNDO / REDO FUNCTIONS *********************/
/*
 * Undo the latest action change by change.
 * Every change is undone by changing the value of node x,y from val after to val before.
 */
void undoAction(Game *gp) {
	int x = 0, y = 0, val_before = 0;
	Action *action = gp->LatestAction;
	Change *curchange = action->changes;

	while(curchange) {
		x = curchange->x;
		y = curchange->y;
		val_before = curchange->val_before;
		setNodeValByType(gp, VALUE, x, y, val_before);
		curchange = curchange->next;
	}
}

/*
 * Redo the latest action change by change.
 * Every change is redone by changing the value of node x,y from val before to val after.
 */
void redoAction(Game *gp) {
	int x = 0, y = 0, val_after = 0;
	Action *action = gp->LatestAction;
	Change *curchange = action->changes;

	while(curchange){
		x = curchange->x;
		y = curchange->y;
		val_after = curchange->val_after;
		setNodeValByType(gp, VALUE, x, y, val_after);
		curchange = curchange->next;
	}
}

/********************* PRINT FUNCTIONS *********************/

static void printVal(int val) {
	/*replace 0 with '_'*/
	if(val == 0){
		printf("_");
	}else{
		printf("%d",val);
	}
}

static void printChangeInner(int x, int y, int val_before, int val_after) {
	printf("%d,%d: ", x, y);

	printf("from ");
	printVal(val_before);

	printf(" to ");
	printVal(val_after);

	printf("\n");
}

/*
 * Prints the correct message while redoing or undoing a change.
 */
void printChange(command_e command, actionType_e actionType, Change *change){
	int x, y;

	/*if the action type is not set then don't print*/
	if(actionType != SET_A){
		return;
	}

	/*x and y for users is lagrer by 1*/
	x = change->x + 1;
	y = change->y + 1;

	/*generic switch for type of action*/
	switch(command){
		case undo:
			printf("Undo ");
			printChangeInner(x, y, change->val_after, change->val_before);
			break;
		case redo:
			printf("Redo ");
			printChangeInner(x, y, change->val_before, change->val_after);
			break;
		default:
			break;
	}

	fflush(stdout);
}

/*
 * print latest action changes for undo
 */
void printUndoChanges(Action *action) {
	Change *curchange = action->changes;

	while(curchange) {
		printChange(undo, action->type, curchange);
		curchange = curchange->next;
	}
}


/*
 * print latest action changes for redo
 */
void printRedoChanges(Action *action) {
	Change *curchange = action->changes;

	while(curchange){
		printChange(redo, action->type, curchange);
		curchange = curchange->next;
	}
}
