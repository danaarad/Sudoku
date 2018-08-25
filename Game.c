/*
 * Game.c
 *
 *  Created on: Aug 24, 2018
 *      Author: Dana Arad
 */

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "Node.h"
#include "Action.h"

Game* initGame(int block_height, int block_width) {
	int rowlen = 0, x = 0, y = 0;
	Node* newNode = NULL;

	Game *gp = (Game*)calloc(1,sizeof(Game));
	gp->blockHeight = block_height;
	gp->blockWidth = block_width;
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


void freeAllActions(Game* gp){
	freeActionsBefore(gp->LatestAction);
	freeActionsAfter(gp->LatestAction);
	freeSingleAction(gp->LatestAction);
}

void freeGameBoard(Game* gp){
	int x, y, rowlen;
	Node* node;

	rowlen = (gp->blockHeight)*(gp->blockWidth);
	for (x = 0; x < rowlen; x++){
		for (y = 0; y < rowlen; y++){
			node = &(gp->gameBoard[x][y]);
			free(node);
		}
		free(gp->gameBoard[x]);
	}
	free(gp->gameBoard);
}

void freeGame(Game* gp){
	freeAllActions(gp);
	freeGameBoard(gp);
	free(gp);
}
