/*
 * change.s
 *
 *  Created on: Sep 5, 2018
 *      Author: Dana Arad
 */
#include "change.h"
#include "settings.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Creates a change and adds it after previous change.
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

static void printVal(int val) {
	/*replace 0 with '_'*/
	if(val == 0){
		printf("_ ");
	}else{
		printf("%d ",val);
	}
}

static void printChangeInner(int x, int y, int val_before, int val_after) {
	printf("%d,%d: ", x, y);

	printf("from ");
	printVal(val_before);

	printf("to ");
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


