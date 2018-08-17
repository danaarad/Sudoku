/*
 * Node.h
 *
 *  Created on: 17 ���� 2018
 *      Author: yael sapir
 */

#ifndef NODE_H_
#define NODE_H_

#include "Game.h"

typedef struct Node {
	int value;
	int isGiven;
	int solution;
	int tempValue;
	int isError;
}Node;

int varifyValue(Game* gp, int x, int y, int z);
int getValue(Game* gp, int x, int y);

int varifyTempValue(Game* gp, int x, int y, int z);
int getTempValue(Game* gp, int x, int y);

int setNodeValue(Game* gp, int x, int y, int z);
int setNodeGiven(Game* gp, int x, int y, int z);
int setNodeSolution(Game* gp, int x, int y, int z);
int setNodeTemp(Game* gp, int x, int y, int z);
int setNodeError(Game* gp, int x, int y, int z);

int getNodeValue(Game* gp, int x, int y);
int getNodeGiven(Game* gp, int x, int y);
int getNodeSolution(Game* gp, int x, int y);
int getNodeTemp(Game* gp, int x, int y);
int getNodeError(Game* gp, int x, int y);

#endif /* NODE_H_ */
