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
    int data;
    struct node *next;
} stack_node;


void display();
void push(int, stack_node *top);
int pop(stack_node *top, int *value);


#endif /* STACK_H_ */
