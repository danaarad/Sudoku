/*
 * Game.c
 *
 *  Created on: Aug 24, 2018
 *      Author: Dana Arad
 */

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

Game* initGame(int block_height, int block_width) {
	int rowlen = 0, x = 0, y = 0;
	Node* newNode = NULL;

	Game *gp = (Game*)malloc(sizeof(Game));
	gp->blockHeight = block_height;
	gp->blockWidth = block_width;
	gp->isErrornous = 0;
	gp->isSolvable = 0;
	gp->markErrors = 0;
	gp->LatestAction = NULL;
	gp->mode = INIT;

	rowlen = block_height*block_width;
	gp->gameBoard = (Node**)calloc(rowlen,sizeof(Node*));

	for (x = 0; x < rowlen; x++){
		gp->gameBoard[x]=(Node*)calloc(rowlen,sizeof(Node));
		for (y = 0; y < rowlen; y++){
			newNode = initNode();
			gp->gameBoard[x][y] = *newNode;
		}
	}

	return gp;
}

int isErrornousBoard(Game* gp) {
	return 0;
}

int isSolvableBoard(Game* gp){
	return 0;
}
