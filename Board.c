/*
 * Board.c
 *
 *  Created on: May 22, 2018
 *      Author: Dana Arad
 */

#include "Game.h"
#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node gameBoard[ROW_SIZE][COL_SIZE];
int isUpdatedSol = 0;


int getValGameorTemp(int x, int y, int isGame){
	int val = 0;
	if (isGame){
		val = getNodeValue(x, y);
	}else{
		val = getNodeTemp(x, y);
	}
	return val;
}

int varifyValue(int x, int y, int z, int isGame) {
	int i = 0, j = 0, x_corner = 0, y_corner = 0, val = 0;

	/*check row*/
	for (i = 1; i <= ROW_SIZE; ++i){

		val = getValGameorTemp(i,y,isGame);
		if (val==z && i!=x){
			return 0;
		}
	}

	/*check col*/
	for (j = 1; j <= COL_SIZE; ++j){
		val = getValGameorTemp(x,j,isGame);
		if (val==z && j!=y){
			return 0;
		}
	}

	/*check block*/
	x_corner = ((x-1)/BLOCK_WIDTH)*BLOCK_WIDTH + 1;
	y_corner = ((y-1)/BLOCK_HEIGHT)*BLOCK_HEIGHT + 1;
	for (i = x_corner; i < x_corner + BLOCK_WIDTH; ++i){
		for(j = y_corner; j < y_corner + BLOCK_HEIGHT; ++j){
			val = getValGameorTemp(i,j,isGame);
			if (val==z && i!=x && j!=y){
				return 0;
			}
		}
	}
	return 1;
}


int varifyBoard(){
	int i = 0, j = 0, value = 0;

	for (i = 1; i < (ROW_SIZE + 1); i++) {
		for (j = 1; j < (COL_SIZE + 1); j++) {
			value = getNodeValue(i,j);
			if (varifyValue(i, j, value, 1) == 0){
				return 0;
			}
		}
	}
	return 1;
}

int initBoard() {
	int i = 0 , j = 0;

	for (i = 0; i < ROW_SIZE; i++) {
		for (j = 0; j < COL_SIZE; j++) {
			struct Node node = {0,0,0,0};
			gameBoard[i][j] = node;
		}
	}

	return 1;
}

int initTempBoard() {
	int i = 0, j = 0;

	for (i = 1; i <= ROW_SIZE; i++) {
		for (j = 1; j <= COL_SIZE; j++) {
				setNodeTemp(i,j,getNodeValue(i,j));
			}
	}
	return 1;
}

int tempToSolution(){
	int x = 0, y = 0;

	for (x = 1; x <= ROW_SIZE; x++) {
		for (y = 1; y <= COL_SIZE; y++) {
			setNodeSolution(x, y, getNodeTemp(x, y));
			}
	}
	return 1;
}

int setNodeValue(int x, int y, int z){
	return (gameBoard[x-1][y-1].value = z);
}

int setNodeGiven(int x, int y, int z){
	return (gameBoard[x-1][y-1].isGiven = z);
}

int setNodeSolution(int x, int y, int z){
	return (gameBoard[x-1][y-1].solution = z);
}

int setNodeTemp(int x, int y, int z){
	return (gameBoard[x-1][y-1].tempValue = z);
}

int setNodeError(int x, int y, int z){
	return (gameBoard[x-1][y-1].error = z);
}

int getNodeValue(int x, int y){
	return (gameBoard[x-1][y-1].value);
}

int getNodeGiven(int x, int y){
	return (gameBoard[x-1][y-1].isGiven);
}

int getNodeSolution(int x, int y){
	return (gameBoard[x-1][y-1].solution);
}

int getNodeTemp(int x, int y){
	return (gameBoard[x-1][y-1].tempValue);
}

int getNodeError(int x, int y){
	return (gameBoard[x-1][y-1].error);
}



