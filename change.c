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

void freeChanges(Change *change) {
	Change *next;
	if (change != NULL) {
		next = change->next;
		freeChanges(next);
		free(change);
	}
}


int printChange(command_e command, actionType_e actionType, Change *change){
	int x, y, z1, z2;

	if(actionType != SET_A){
		return 0;
	}

	x = change->x + 1;
	y = change->y + 1;

	switch(command){
		case undo:
			printf("Undo ");
			z1 = change->val_after;
			z2 = change->val_before;
			break;
		case redo:
			printf("Redo ");
			z1 = change->val_before;
			z2 = change->val_after;
			break;
		default:
			return 0;
	}
	printf("%d,%d: ", x, y);

	prinf("from ");
	if(z1 == 0){
		printf("_ ");
	}else{
		printf("%d ",z1);
	}

	prinf("to ");
	if(z2 == 0){
		printf("_ ");
	}else{
		printf("%d ",z2);
	}

	printf("\n");
	fflush(stdout);
	return 1;
}


