/*
 * Node.c
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "settings.h"

Node* getNode(Game* gp, int x, int y){
	return &(gp->gameBoard[x][y]);
}

int copyNodetoNode(Node* copyfrom, Node* copyto){
	int valtype = 0, val = 0, worked = 1;
	/*this is problematic because value has to be first and error has to be last*/
	for (valtype = VALUE; valtype <= ISERROR; valtype++){
		val = getNodeValByTypeDirectly(copyfrom, valtype);
		worked *= setNodeValByTypeDirectly(copyto, valtype, val);
	}
	return worked;
}

int getNodeValByType(Game* gp, valType_e valType, int x, int y){
	switch(valType){
	case VALUE: return gp->gameBoard[x][y].value;
	case ISGIVEN: return gp->gameBoard[x][y].isGiven;
	case SOLUTION: return gp->gameBoard[x][y].solution;
	case TEMP: return gp->gameBoard[x][y].tempValue;
	case ISERROR: return gp->gameBoard[x][y].isError;
	}
	return -1;
}

int setNodeValByType(Game* gp, valType_e valType, int x, int y, int val){
	switch(valType){
	case VALUE:
		gp->gameBoard[x][y].value = val;
		break;
	case ISGIVEN:
		gp->gameBoard[x][y].isGiven = val;
		break;
	case SOLUTION:
		gp->gameBoard[x][y].solution = val;
		break;
	case TEMP:
		gp->gameBoard[x][y].tempValue = val;
		break;
	case ISERROR:
		gp->gameBoard[x][y].isError = val;
		break;
	}
	return getNodeValByType(gp, valType, x, y) == val;
}

int getNodeValByTypeDirectly(Node* node, valType_e valType){
	switch(valType){
	case VALUE: return node->value;
	case ISGIVEN: return node->isGiven;
	case SOLUTION: return node->solution;
	case TEMP: return node->tempValue;
	case ISERROR: return node->isError;
	}
	return -1;
}

int setNodeValByTypeDirectly(Node* node, valType_e valType, int val){
	switch(valType){
	case VALUE:
		node->value = val;
		break;
	case ISGIVEN:
		node->isGiven = val;
		break;
	case SOLUTION:
		node->solution = val;
		break;
	case TEMP:
		node->tempValue = val;
		break;
	case ISERROR:
		node->isError = val;
		break;
	}
	return getNodeValByTypeDirectly(node, valType) == val;
}


