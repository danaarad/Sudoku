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
