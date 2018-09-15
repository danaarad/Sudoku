/*
 * stack.c
 *
 *  Contains our simple stack implementation.
 *  Exposed:
 *   - push
 *   - pop
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#include "settings.h"

/*
 * Injects node to top of stack.
 * A new node with attributes x, y and value will become
 * the new stack top and will be returned.
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
 * Fills the x, y and value attributes with the attributes of the stack top.
 * Returns the new stack top.
 * In case the stack top is NULL, NULL is returned, x, y and value are set to -1.
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
		top = top->next;
		free(temp);
    }

	*x = poped_x;
	*y = poped_y;
	*value = poped_value;
    return top;
}


