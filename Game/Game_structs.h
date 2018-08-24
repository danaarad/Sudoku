/*
 * Game_structs.h
 *
 *  Created on: 24 баев 2018
 *      Author: yael sapir
 */

#ifndef GAME_STRUCTS_H_
#define GAME_STRUCTS_H_

#include "Action.h"

typedef struct Node {
	int value;
	int isGiven;
	int solution;
	int tempValue;
	int isError;
}Node;

typedef enum valType {
	VALUE,
	ISGIVEN,
	SOLUTION,
	TEMP,
	ISERROR
} valType_e;

typedef struct Game {
	int blockHeight;
	int blockWidth;
	Node** gameBoard;
	mode_e mode;
	int isErrornous;
	int isSolvable;
	int markErrors;
	Action* LatestAction;
}Game;


#endif /* GAME_STRUCTS_H_ */
