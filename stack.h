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


stack_node *push(stack_node *top, int x, int y, int value);
stack_node *pop(stack_node *top, int *x, int *y, int *value);


#endif /* STACK_H_ */
