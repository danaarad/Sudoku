/*
 * Node.c
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"

int varifyValue(Game* gp, int x, int y, int z);
int getValue(Game* gp, int x, int y);

int varifyTempValue(Game* gp, int x, int y, int z);
int getTempValue(Game* gp, int x, int y);

int getNodeValue(Game* gp, int x, int y){
	return gp->gameBoard[x][y].value;
}
int getNodeGiven(Game* gp, int x, int y){
	return gp->gameBoard[x][y].isGiven;
}
int getNodeSolution(Game* gp, int x, int y){
	return gp->gameBoard[x][y].solution;
}
int getNodeTemp(Game* gp, int x, int y){
	return gp->gameBoard[x][y].tempValue;
}
int getNodeError(Game* gp, int x, int y){
	return gp->gameBoard[x][y].isError;
}

int setNodeValue(Game* gp, int x, int y, int value){
	Node node = gp->gameBoard[x][y];
	node.value = value;
	return node.value == value;
}
int setNodeGiven(Game* gp, int x, int y, int isgiven){
	Node node = gp->gameBoard[x][y];
	node.isGiven = isgiven;
	return node.isGiven == isgiven;
}
int setNodeSolution(Game* gp, int x, int y, int sol){
	Node node = gp->gameBoard[x][y];
	node.solution = sol;
	return node.solution == sol;
}
int setNodeTemp(Game* gp, int x, int y, int temp){
	Node node = gp->gameBoard[x][y];
	node.tempValue = temp;
	return node.tempValue == temp;
}
int setNodeError(Game* gp, int x, int y, int iserror){
	Node node = gp->gameBoard[x][y];
	node.isError = iserror;
	return node.isError == iserror;
}



