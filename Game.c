/*
 * Game.c
 *
 *  Created on: Aug 24, 2018
 *      Author: Dana Arad
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Game.h"
#include "Node.h"
#include "Action.h"
#include "settings.h"
#include "GameAux.h"
#include "arrayAux.h"
#include "solver.h"

/*
 * Returns a pointer to a new game of size NxN (N = block_height*block_width);
 * Sets LatestAction to an action of type INIT.
 * Allocates place for board with nodes that are all 0;
 */
Game* initGame(int block_height, int block_width) {
	int rowlen = 0, x = 0;

	Game *gp = (Game*)calloc(1,sizeof(Game));
	if(gp){
		gp->blockHeight = block_height;
		gp->blockWidth = block_width;
		gp->N = block_height*block_width;
		gp->mode = INIT;
		gp->markErrors = 1;
		gp->LatestAction = initAction(INIT_A, 0, 0);
		if (!gp->LatestAction){
			printf(CALLOC_ERROR);
			free(gp);
			return NULL;
		}
	}else{
		printf(CALLOC_ERROR);
		return NULL;
	}

	rowlen = gp->N;
	gp->gameBoard = (Node**)calloc(rowlen,sizeof(Node*));

	if(gp->gameBoard){
		for (x = 0; x < rowlen; x++){
			gp->gameBoard[x]=(Node*)calloc(rowlen,sizeof(Node));

			if(!gp->gameBoard[x]){
				free(gp->LatestAction);
				free(gp->gameBoard);
				free(gp);
				printf(CALLOC_ERROR);
				return NULL;
			}
		}
	}else{
		printf(CALLOC_ERROR);
		free(gp->LatestAction);
		free(gp);
		return NULL;
	}

	return gp;
}

/*
 * Sets all values of type TEMP to 0 for all nodes.
 * This creates an alternative board with alternative values (currently 0).
 */
int initTempBoard(Game* gp){
	int rowlen = gp->N;
	int i, j;

	for (i = 0; i < rowlen; i++){
		for (j = 0; j < rowlen; j++){
			setNodeValByType(gp, TEMP, i, j, 0);
		}
	}

	return 1;
}

/*
 * All nodes have an ISERROR boolean value.
 * If one of the nodes has a true ISERROR field, it is an error and the board is errorneous.
 */
int isErrornousBoard(Game* gp) {
	int N = gp->N, i = 0, j = 0;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (getNodeValByType(gp,ISERROR, i, j) == 1){
				return 1;
			}
		}
	}
	return 0;
}

/*
 * All nodes have an ISERROR boolean value.
 * If a node has a true ISERROR field, it is an error and it is counted as such.
 */
int CountErrorsInBoard(Game* gp) {
	int N = gp->N, i = 0, j = 0, numOfErrors = 0;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (getNodeValByType(gp, ISERROR, i, j) == 1){
				numOfErrors++;
			}
		}
	}
	return numOfErrors;
}

/*
 * Returned number of filled nodes in board
 */
int CountValuesInBoard(Game* gp) {
	int N = gp->N, i = 0, j = 0, numOfValues = 0;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (getNodeValByType(gp, VALUE, i, j) != 0){
				numOfValues++;
			}
		}
	}
	return numOfValues;
}

/*
 * Frees all actions before and after action (recursively).
 * Frees action.
 */
void freeAllActions(Game* gp){
	freeActionsBefore(gp->LatestAction);
	freeActionsAfter(gp->LatestAction);
	freeSingleAction(gp->LatestAction);
}

/*
 * Frees all arrays of nodes from 2D node array.
 * Frees the gameBoard.
 */
void freeGameBoard(Game* gp){
	int x, rowlen;

	rowlen = gp->N;
	for (x = 0; x < rowlen; x++){
		free(gp->gameBoard[x]);
	}
	free(gp->gameBoard);
}

/*
 * Frees the actions (and all the changes within),
 * Frees the game board (and all nodes within),
 * Frees the game.
 */
void freeGame(Game* gp){
	freeAllActions(gp);
	freeGameBoard(gp);
	free(gp);
}

/*
 * Creates a check table foe every row, col and block.
 * A check table is a 3D array that contains x,y values by value.
 * The check table is then sent to "updateErrorsFromCheckTable"
 * that updates the errors respectively.
 */
int UpdateErrors(Game *gp){
	int x, y, val, idx, emptyPlace, x_corner, y_corner;
	int blockWidth = gp->blockWidth;
	int blockHeight = gp->blockHeight;
	int rowSize = gp->N;
	int ***checkTable;
	int ErrorNum = 0;

	/*calloc checkTable*/
	checkTable = callocCheckTable(rowSize);
	if (!checkTable){
		return -1;
	}

	/*all is set to -1*/
	resetCheckTable(checkTable, rowSize);
	initTempBoard(gp);

	/*check the rows*/
	for (y = 0; y < rowSize; y++){
		for (x = 0; x < rowSize; x++){
			val = getNodeValByType(gp, VALUE, x, y);
			if(val > 0){
				idx = val-1;
				/*insert x and y into checkTable*/
				emptyPlace = findFirstFreeCellIn2DArr(checkTable[idx], rowSize);
				checkTable[idx][emptyPlace][0] = x;
				checkTable[idx][emptyPlace][1] = y;
			}
		}
		updateErrorsFromCheckTable(gp, checkTable, rowSize);
		resetCheckTable(checkTable, rowSize);
	}

	/*check the cols*/
	for (x = 0; x < rowSize; x++){
		for (y = 0; y < rowSize; y++){
			val = getNodeValByType(gp, VALUE, x, y);
			if(val > 0){
				idx = val-1;
				/*insert x and y into checkTable*/
				emptyPlace = findFirstFreeCellIn2DArr(checkTable[idx], rowSize);
				checkTable[idx][emptyPlace][0] = x;
				checkTable[idx][emptyPlace][1] = y;
			}
		}
		updateErrorsFromCheckTable(gp, checkTable, rowSize);
		resetCheckTable(checkTable, rowSize);
	}

	/*check the blocks*/
	for (x_corner = 0; x_corner < rowSize; x_corner+=blockWidth){
		for (y_corner = 0; y_corner < rowSize; y_corner+=blockHeight){
			for (x = x_corner; x < x_corner + blockWidth; ++x){
				for(y = y_corner; y < y_corner + blockHeight; ++y){
					val = getNodeValByType(gp, VALUE, x, y);
					if(val > 0){
						idx = val-1;
						/*insert x and y into checkTable*/
						emptyPlace = findFirstFreeCellIn2DArr(checkTable[idx], rowSize);
						checkTable[idx][emptyPlace][0] = x;
						checkTable[idx][emptyPlace][1] = y;
					}
				}
			}
			updateErrorsFromCheckTable(gp, checkTable, rowSize);
			resetCheckTable(checkTable, rowSize);
		}
	}

	freeCheckTable(checkTable, rowSize);
	ErrorNum = CountErrorsInBoard(gp);
	initTempBoard(gp);
	return (ErrorNum);

}


int moveValueToTemp(Game *game) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int value = 0;

	for (y = 0; y < N; ++y) {
		for (x = 0; x < N; ++x) {
			value = getNodeValByType(game, VALUE, x, y);
			setNodeValByType(game, TEMP, x , y, value);
		}
	}
	return 1;

}
