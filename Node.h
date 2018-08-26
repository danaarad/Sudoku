/*
 * Node.h
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */

#ifndef NODE_H_
#define NODE_H_

#include "Game_structs.h"

int varifyValue(Game* gp, valType_e valType, int x, int y, int z);
Node* initNode();
Node* cloneNode(Game* gp, int x, int y);
int setNodeValByType(Game* gp, valType_e valType, int x, int y, int val);
int getNodeValByType(Game* gp, valType_e valType, int x, int y);


#endif /* NODE_H_ */
