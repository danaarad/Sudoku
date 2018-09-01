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

int updateErrorsFromCheckTable(Game *gp, int ***checkTable, int lenOfArr){
	int i, j, x, y, firstEmpty, newErrorNum = 0;

	for(i = 0; i < lenOfArr; i++){
		firstEmpty = findFirstFreeCellIn2DArr(checkTable[i], lenOfArr);
		/*if this is a value that only one node has*/
		if (firstEmpty == 1){
			x = checkTable[i][0][0];
			y = checkTable[i][0][1];
			setNodeValByType(gp, ISERROR, x, y, 0);
		}/*if this is a value that multiple nodes have*/
		else if(firstEmpty > 1){
			for (j = 0; j < firstEmpty; j++){
				x = checkTable[i][j][0];
				y = checkTable[i][j][1];
				/*if this was not an error before*/
				if (getNodeValByType(gp, ISERROR, x, y)==0 || getNodeValByType(gp, ISGIVEN, x, y)==0){
					newErrorNum++;
					setNodeValByType(gp, ISERROR, x, y, 1);
				}
			}
		}
	}
	return newErrorNum;
}

void freeCheckTable(int ***checkTable, int rowSize){
	int i, j;
	for (i = 0; i < rowSize; ++i){
		for (j = 0; j < rowSize; ++j){
			free(checkTable[i][j]);
		}
		free(checkTable[i]);
	}
	free(checkTable);
}

int ***callocCheckTable(int rowSize){
	int i, j;
	int ***checkTable = (int***)calloc(rowSize,sizeof(int**));
		if(checkTable){
			for (i = 0; i < rowSize; ++i){
				checkTable[i] = (int**)calloc(rowSize,sizeof(int*));
				if(checkTable[i]){
					for (j = 0; j < rowSize; ++j){
						checkTable[i][j] = (int*)calloc(2,sizeof(int*));
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

