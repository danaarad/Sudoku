/*
 * Node.h
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */

#ifndef NODE_H_
#define NODE_H_


typedef struct Node {
	int value;
	int isGiven;
	int solution;
	int tempValue;
	int error;
}Node;

int varifyValue(int x, int y, int z);
int getValue(int x, int y);

int varifyTempValue(int x, int y, int z);
int getTempValue(int x, int y);

int setNodeValue(int x, int y, int z);
int setNodeGiven(int x, int y, int z);
int setNodeSolution(int x, int y, int z);
int setNodeTemp(int x, int y, int z);
int setNodeError(int x, int y, int z);

int getNodeValue(int x, int y);
int getNodeGiven(int x, int y);
int getNodeSolution(int x, int y);
int getNodeTemp(int x, int y);
int getNodeError(int x, int y);

#endif /* NODE_H_ */
