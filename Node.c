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

int varifyValue(Game* gp, valType_e valType, int x, int y, int val){
	int i = 0, j = 0, x_corner = 0, y_corner = 0, otherVal = 0;
	int rowSize, colSize, blockWidth, blockHeidth;

	blockWidth = gp->blockWidth;
	blockHeight = gp->blockHieght;
	rowSize = colSize = blockWidth*blockHeight;

	/*check row*/
	for (i = 1; i <= rowSize; ++i){

		otherVal = getNodeValByType(gp, valType, i, y);
		if (otherVal == val && i != x){
			return 0;
		}
	}

	/*check col*/
	for (j = 1; j <= colSize; ++j){
		otherVal = getNodeValByType(gp, valType, x, j);
		if (otherVal == val && j != y){
			return 0;
		}
	}

	/*check block*/
	x_corner = ((x-1)/blockWidth)*blockWidth + 1;
	y_corner = ((y-1)/blockHeight)*blockHeight + 1;
	for (i = x_corner; i < x_corner + blockWidth; ++i){
		for(j = y_corner; j < y_corner + blockHeight; ++j){
			otherVal = getNodeValByType(gp, valType, x, y);
			if (otherVal == val && i != x && j != y){
				return 0;
			}
		}
	}
	return 1;
}
int getNodeValByType(Game* gp, valType_e valType, int x, int y){
	switch(valType){
	case VALUE: return gp->gameBoard[x][y].value;
	case ISGIVEN: return gp->gameBoard[x][y].isGiven;
	case SOLUTION: return gp->gameBoard[x][y].solution;
	case TEMP: return gp->gameBoard[x][y].tempValue;
	case ISERROR: return gp->gameBoard[x][y].isError;
	}
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
	return getNodeValByType(gp, valType, x, y);
}



