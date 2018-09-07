/*
 * Node.c
 *
 *  Created on: 17 ���� 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "settings.h"

/*
 * The function gets type, x, y and returns
 * the value (by type) of the node in position x,y.
 */
int getNodeValByType(Game* gp, valType_e valType, int x, int y) {
	switch (valType) {
	case VALUE:
		return gp->gameBoard[x][y].value;
	case ISGIVEN:
		return gp->gameBoard[x][y].isGiven;
	case TEMP:
		return gp->gameBoard[x][y].tempValue;
	case ISERROR:
		return gp->gameBoard[x][y].isError;
	}
	return -1;
}

/*
 * The function gets type, x, y, val and sets
 * the value (by type) of the node in position x,y.
 */
void setNodeValByType(Game* gp, valType_e valType, int x, int y, int val) {
	switch (valType) {
	case VALUE:
		gp->gameBoard[x][y].value = val;
		if (val == 0) {
			gp->gameBoard[x][y].isError = 0;
		}
		break;
	case ISGIVEN:
		gp->gameBoard[x][y].isGiven = val;
		break;
	case TEMP:
		gp->gameBoard[x][y].tempValue = val;
		break;
	case ISERROR:
		gp->gameBoard[x][y].isError = val;
		break;
	}
}

