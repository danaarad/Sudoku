/*
 * Node.h
 *
 *  Created on: 17 ���� 2018
 *      Author: yael sapir
 */

#ifndef NODE_H_
#define NODE_H_

#include "Game_structs.h"

void setNodeValByType(Game* gp, valType_e valType, int x, int y, int val);
int getNodeValByType(Game* gp, valType_e valType, int x, int y);
#endif /* NODE_H_ */
