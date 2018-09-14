/*
 * stack.c
 *
 *  Created on: Sep 1, 2018
 *      Author: Dana Arad
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "settings.h"

/*
 * Inject node to top of stack.
 */
stack_node *push(stack_node *top, int x, int y, int value) {
    struct node *nptr = malloc(sizeof(struct node));
    if (nptr == NULL) {
    	printf(MALLOC_ERROR);
    	return NULL;
    }
    nptr->x = x;
    nptr->y = y;
    nptr->value = value;
    nptr->next = top;
    return nptr;
}

/*
 * Return and remove stack top.
 */
stack_node *pop(stack_node *top, int *x, int *y, int *value) {
	stack_node *temp;
	int poped_x = -1;
	int poped_y = -1;
	int poped_value = -1;

    if (top != NULL) {
    	temp = top;
		poped_x = top->x;
		poped_y = top->y;
		poped_value = top->value;
		*x = poped_x;
		*y = poped_y;
		*value = poped_value;
		top = top->next;
		free(temp);
		return top;
    }
    return NULL;
}


