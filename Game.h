/*
 * Game.h
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */

#ifndef GAME_H_
#define GAME_H_

#include "Game_structs.h"

Game* initGame(int block_height, int block_width);
int setLatestAction(Game* gp, Action *action, int isConnected);
int isErrornousBoard(Game* gp);
int isSolvableBoard(Game* gp);
void freeGame(Game* gp);
int UpdateErrors(Game *gp);
int initTempBoard(Game* gp);
int moveValueToTemp(Game *game);



#endif /* GAME_H_ */
