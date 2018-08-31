/*
 * Node.h
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */

#ifndef NODE_H_
#define NODE_H_

#include "Game_structs.h"

Node* initNode();
Node* getNode(Game* gp, int x, int y);
Node* cloneNode(Node *orignode);
int copyNodetoNode(Node* copyfrom, Node* copyto);
int setNodeValByType(Game* gp, valType_e valType, int x, int y, int val);
int getNodeValByType(Game* gp, valType_e valType, int x, int y);
int getNodeValByTypeDirectly(Node* node, valType_e valType);
int setNodeValByTypeDirectly(Node* node, valType_e valType, int val);

#endif /* NODE_H_ */
