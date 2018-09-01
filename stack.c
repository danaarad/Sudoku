/*
 * stack.c
 *
 *  Created on: Sep 1, 2018
 *      Author: Dana Arad
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(int item, stack_node *top)
{
    struct node *nptr = malloc(sizeof(struct node));
    nptr->data = item;
    nptr->next = top;
    top = nptr;
}

void display(stack_node *top) {
    struct node *temp;

    temp = top;
    while (temp != NULL)
    {
        printf("\n%d", temp->data);
        temp = temp->next;
    }
}

int pop(stack_node *top, int *value) {
	stack_node *temp;
	int poped_value = 0;

    if (top == NULL) {
        return 0;
    } else {
    	temp = top;
    	poped_value = top->data;
    	*value = poped_value;
		top = top->next;
		free(temp);
		return 1;

    }
}
