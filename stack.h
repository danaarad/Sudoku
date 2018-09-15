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
 * Injects node to top of stack.
 * A new node with attributes x, y and value will become
 * the new stack top and will be returned.
 */
stack_node *push(stack_node *top, int x, int y, int value);

/*
 * Fills the x, y and value attributes with the attributes of the stack top.
 * Returns the new stack top.
 * In case the stack top is NULL, NULL is returned, x, y and value are set to -1.
 */
stack_node *pop(stack_node *top, int *x, int *y, int *value);


#endif /* STACK_H_ */
