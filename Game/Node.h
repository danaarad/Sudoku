/*
 * Node.h
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */

#ifndef NODE_H_
#define NODE_H_


#include "Game.h"
#include "Node.h"
#include "../settings.h"
#include "Game_structs.h"

typedef struct Node {
	int value;
	int isGiven;
	int solution;
	int tempValue;
	int isError;
}Node;

typedef enum valType {
	VALUE,
	ISGIVEN,
	SOLUTION,
	TEMP,
	ISERROR
} valType_e;


int varifyValue(Game* gp, valType_e valType, int x, int y, int z);

int setNodeValByType(Game* gp, valType_e valType, int x, int y, int val);
int getNodeValByType(Game* gp, valType_e valType, int x, int y);


#endif /* NODE_H_ */
