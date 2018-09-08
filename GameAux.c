/*
 * GameAux.c
 *
 *  Created on: 31 баев 2018
 *      Author: yael sapir
 */

#include <stdlib.h>
#include <stdio.h>
#include "settings.h"
#include "Game_structs.h"
#include "arrayAux.h"
#include "Node.h"


void printCheckTable(int ***checkTable, int lenOfArr){
	int val, num;
	for (val = 1; val <= lenOfArr; val++){
		printf(" ~%d~ ",val);
	}printf("\n");
	fflush(stdout);
	for (num = 0; num < lenOfArr; num++){
		for (val = 0; val < lenOfArr; val++){
			if (checkTable[val][num][0]!=-1){
				printf("(%d,%d)",checkTable[val][num][0],checkTable[val][num][1]);
			}else{
				printf("     ");
			}
		}printf("\n");
	}printf("\n");
	fflush(stdout);
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
	int i, j;
	int ***checkTable = (int***)calloc(N,sizeof(int**));
	if(checkTable){
		for (i = 0; i < N; ++i){
			checkTable[i] = (int**)calloc(N,sizeof(int*));
			if(checkTable[i]){
				for (j = 0; j < N; ++j){
					checkTable[i][j] = (int*)calloc(2,sizeof(int));
					if(!checkTable[i][j]){
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

