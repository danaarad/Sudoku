/*
 * solver.c
 *
 *  Created on: Aug 31, 2018
 *      Author: Dana Arad
 */
#include "solver.h"

int isSolvable(Game* gp) {
	return 1;
}

int fill_nodes_random(Game *game, int x) {
	return 1;
}

int fill_nodes_ILP(Game *game) {
	return 1;
}

int clear_nodes(Game *game, int y) {
	return 1;
}

int exhaustive_backtracking(Game *game){
	return 0;
}

int get_possible_values_for_node(Game *game, int x, int y, int *possible_values) {
	return 1;
}

int isPossibleValue(Game* gp, valType_e valType, int x, int y, int valToCheck){
	int i = 0, j = 0, x_corner = 0, y_corner = 0, otherVal = 0;
	int rowSize, colSize, blockWidth, blockHeight;
	blockWidth = gp->blockWidth;
	blockHeight = gp->blockHeight;
	rowSize = colSize = blockWidth*blockHeight;

	/*check row*/
	for (i = 0; i < rowSize; ++i){
		otherVal = getNodeValByType(gp, valType, i, y);
		if (otherVal == valToCheck && i != x){
			return 0;
		}
	}

	/*check col*/
	for (j = 0; j < colSize; ++j){
		otherVal = getNodeValByType(gp, valType, x, j);
		if (otherVal == valToCheck && j != y){
			return 0;
		}
	}

	/*check block*/
	x_corner = (x/blockWidth)*blockWidth;
	y_corner = (y/blockHeight)*blockHeight;
	for (i = x_corner; i < x_corner + blockWidth; ++i){
		for(j = y_corner; j < y_corner + blockHeight; ++j){
			otherVal = getNodeValByType(gp, valType, i, j);
			if (otherVal == valToCheck && i != x && j != y){
				return 0;
			}
		}
	}
	return 1;
}
