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
#include "settings.h"

Game* initGame(int block_height, int block_width) {
	int rowlen = 0, x = 0, y = 0, i = 0;
	Node* newNode = NULL;

	Game *gp = (Game*)calloc(1,sizeof(Game));
	if(gp){
		gp->blockHeight = block_height;
		gp->blockWidth = block_width;
		gp->mode = INIT;
	}else{
		printf(CALLOC_ERROR);
		return NULL;
	}

	rowlen = block_height*block_width;
	gp->gameBoard = (Node**)calloc(rowlen,sizeof(Node*));

	if(gp->gameBoard){
		for (x = 0; x < rowlen; x++){
			gp->gameBoard[x]=(Node*)calloc(rowlen,sizeof(Node));

			if(gp->gameBoard[x]){
				for (y = 0; y < rowlen; y++){
					newNode = initNode();
					gp->gameBoard[x][y] = *newNode;
				}
			}else{
				for (i = 0; i <= x; i++){
					free(gp->gameBoard[i]);
				}
				free(gp);
				printf(CALLOC_ERROR);
				return NULL;
			}
		}
	}else{
		printf(CALLOC_ERROR);
		free(gp);
		return NULL;
	}

	return gp;
}

int isErrornousBoard(Game* gp) {
	return 0;
}

int isSolvableBoard(Game* gp){
	return 0;
}

int setLatestAction(Game* gp, Action *action, int isConnected){
	return setNextAction(gp->LatestAction, action, isConnected);
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
