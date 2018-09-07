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

int getNodeValByType(Game* gp, valType_e valType, int x, int y){
	switch(valType){
	case VALUE: return gp->gameBoard[x][y].value;
	case ISGIVEN: return gp->gameBoard[x][y].isGiven;
	case TEMP: return gp->gameBoard[x][y].tempValue;
	case ISERROR: return gp->gameBoard[x][y].isError;
	}
}

void setNodeValByType(Game* gp, valType_e valType, int x, int y, int val){
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
}


