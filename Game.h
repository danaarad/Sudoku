/*
 * Game.h
 *
 *  Created on: 17 ���� 2018
 *      Author: yael sapir
 */

#ifndef GAME_H_
#define GAME_H_

#include "Node.h"
#include "Action.h"

typedef struct Game {
	int blockHeight;
	int blockWidth;
	Node** gameBoard;
	mode_e mode;
	int isErrornous;
	int isSolvable;
	Actoion* LatestAction

}Game;

Game* initGame(int block_height, int block_width);
int isErrornousBoard();
int isSolvableBoard();


#endif /* GAME_H_ */