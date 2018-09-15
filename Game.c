/*
 * Game.c
 *
 *  Contains our Game interface implementation
 *  Each function is documented below
 *
 *  This file contains:
 *  - Node getters and setters
 *  - Check Table function:
 *  	A Check Table object is used to update the errors in the game board.
 *  	This sections contains it's init, free and operational functions
 *  - Game functions:
 *  	functions that are used to perform operation on a game object
 *  - Free functions
 *  - Error handling functions:
 *  	Function that are used to handle errors in the game board
 *
 */

#include "game.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "action.h"
#include "settings.h"
#include "solver.h"


/************************* NODE GETTER AND SETTER FUNCTIONS ******************************/
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

/************************* CHECK TABLE FUNCTIONS ******************************/

/*
 * Returns the index of the first zero value in a 2d array.
 * This function is used for working with check tables.
 */
static int findFirstFreeCellIn2DArr(int **Arr2D, int lenOfArr){
	int i;
	for (i = 0; i < lenOfArr; i++){
		if (Arr2D[i][0] == -1){
			return i;
		}
	}
	return lenOfArr;
}

/*
 * This function receives a check table representing a row, col or block.
 * It goes over the values, if more than one node in the section
 * share the same value, they are marked as errors and are marked in the TEMP value.
 * This insures that values that are errors once will remain errors throughout the
 * whole check process.
 */
int updateErrorsFromCheckTable(Game *gp, int ***checkTable, int lenOfArr){
	int val, i, x, y, firstEmpty;

	for(val = 0; val < lenOfArr; val++){
		firstEmpty = findFirstFreeCellIn2DArr(checkTable[val], lenOfArr);
		/*if there are multiple nodes of this val in the same check table, they are errors*/
		if(firstEmpty > 1){
			for (i = 0; i < firstEmpty; i++){
				/*get x y from checkTable*/
				x = checkTable[val][i][0];
				y = checkTable[val][i][1];

				setNodeValByType(gp, ISERROR, x, y, 1);
				setNodeValByType(gp, TEMP, x, y, 1);
			}
		}


		/*in this case, there is one node of this val in the checked segment.
		 * This does not mean it isn't an error.*/
		else if (firstEmpty == 1){
			x = checkTable[val][0][0];
			y = checkTable[val][0][1];

			/*This node was not an error in previous segments*/
			if(getNodeValByType(gp, TEMP, x, y) == 0){
				setNodeValByType(gp, ISERROR, x, y, 0);
			}
		}
	}
	return 1;
}

/*
 * Free the check table on all dimensions.
 */
void freeCheckTable(int ***checkTable, int N){
	int i, j;
	for (i = 0; i < N; ++i){
		for (j = 0; j < N; ++j){
			free(checkTable[i][j]);
		}
		free(checkTable[i]);
	}
	free(checkTable);
}

/*
 * Allocs the check table on all dimensions.
 * The check table is built in the following manner:
 *
 *   ~1~    ~2~    ~3~  ...
 * (x1,y1)       (x2,y2)
 * (x3,y3)
 *   ...
 *
 * for each value, a 2D table contains all x,y values that have that value.
 */
int ***callocCheckTable(int N){
	int i = 0, j = 0;
	int ***checkTable = (int***) calloc(N, sizeof(int**));
	if (checkTable) {
		for (i = 0; i < N; ++i) {
			checkTable[i] = (int**) calloc(N, sizeof(int*));
			if (checkTable[i]) {
				for (j = 0; j < N; ++j) {
					checkTable[i][j] = (int*) calloc(2,sizeof(int));
					if (!checkTable[i][j]) {
						printf(CALLOC_ERROR);
						return NULL;
					}
				}
			}else{
				printf(CALLOC_ERROR);
				return NULL;
			}
		}
	}else{
		printf(CALLOC_ERROR);
		return NULL;
	}
	return checkTable;
}

/*
 * Sets all values in check table to -1
 */

int resetCheckTable(int ***checkTable, int rowSize){
	int i,j;
	for (i = 0; i < rowSize; i++){
		for (j = 0; j < rowSize; j++){
			checkTable[i][j][0] = -1;
			checkTable[i][j][1] = -1;
		}
	}
	return 1;
}

/************************ GAME FUNCTIONS ***************************/
/*
 * Returns a pointer to a new game of size NxN (N = block_height*block_width);
 * Sets LatestAction to an action of type INIT_A.
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
		if (!gp->LatestAction) {
			free(gp);
			return NULL;
		}
	} else {
		printf(CALLOC_ERROR);
		return NULL;
	}

	rowlen = gp->N;
	gp->gameBoard = (Node**) calloc(rowlen, sizeof(Node*));

	if (gp->gameBoard) {
		for (x = 0; x < rowlen; x++) {
			gp->gameBoard[x] = (Node*) calloc(rowlen, sizeof(Node));

			if (!gp->gameBoard[x]) {
				free(gp->LatestAction);
				free(gp->gameBoard);
				free(gp);
				printf(CALLOC_ERROR);
				return NULL;
			}
		}
	} else {
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
int clearBoardByValType(Game* gp, valType_e val_type){
	int rowlen = gp->N;
	int i = 0, j = 0;

	for (i = 0; i < rowlen; i++) {
		for (j = 0; j < rowlen; j++) {
			setNodeValByType(gp, val_type, i, j, 0);
		}
	}

	return 1;
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


/************************* FREE FUNCTIONS ******************************/

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


/************************* ERROR HANDLING FUNCTIONS ******************************/

/*
 * All nodes have an ISERROR boolean value.
 * If one of the nodes has a true ISERROR field, it is an error and the board is erroneous.
 */
int isErroneousBoard(Game* gp) {
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
 * Creates a check table for every row, col and block.
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
	clearBoardByValType(gp, TEMP);

	/*check the rows*/
	for (y = 0; y < rowSize; y++){
		for (x = 0; x < rowSize; x++){
			val = getNodeValByType(gp, VALUE, x, y);
			if(val > 0) {
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
	clearBoardByValType(gp, TEMP);
	return (ErrorNum);

}
