/*
 * stack.h
 *
 *  Created on: Sep 1, 2018
 *      Author: Dana Arad
 */

#ifndef STACK_H_
#define STACK_H_

typedef struct node
{
    int x;
    int y;
    int value;
    struct node *next;
} stack_node;

/*
 * Inject node to top of stack.
 * The new node will become the new stack top and will be returned.
 */
stack_node *push(stack_node *top, int x, int y, int value);

/*
 * Return and remove stack top.
 */
stack_node *pop(stack_node *top, int *x, int *y, int *value);


#endif /* STACK_H_ */
