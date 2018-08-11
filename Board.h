/*
 * Board.h
 *
 *  Created on: May 22, 2018
 *      Author: Dana Arad
 */

#ifndef BOARD_H_
#define BOARD_H_

extern int BLOCK_HEIGHT =  3;
extern int BLOCK_WIDTH =  3;

#define BLOCK_SIZE (BLOCK_HEIGHT*BLOCK_WIDTH)
#define ROW_SIZE (BLOCK_HEIGHT*BLOCK_WIDTH)
#define COL_SIZE (BLOCK_HEIGHT*BLOCK_WIDTH)


typedef struct Node {
	int value;
	int isGiven;
	int solution;
	int tempValue;
	int error;
}Node;

int initBoard(int block_height, int block_width);
int initTempBoard();
int isErrornousBoard();
int isSolvableBoard();

int tempToSolution();

int varifyValueGame(int x, int y, int z);
int getValGame(int x, int y);

int varifyValueTemp(int x, int y, int z);
int getValTemp(int x, int y);

int setNodeValue(int x, int y, int z);
int setNodeGiven(int x, int y, int z);
int setNodeSolution(int x, int y, int z);
int setNodeTemp(int x, int y, int z);
int setNodeError(int x, int y, int z);

int getNodeValue(int x, int y);
int getNodeGiven(int x, int y);
int getNodeSolution(int x, int y);
int getNodeTemp(int x, int y);
int getNodeError(int x, int y);

#endif /* BOARD_H_ */
