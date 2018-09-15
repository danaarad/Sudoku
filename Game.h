/*
 * Game.h
 *
 *  Created on: 17 баев 2018
 *      Author: yael sapir
 */

#ifndef GAME_H_
#define GAME_H_

#include "Game_structs.h"


/************************* NODE GETTER AND SETTER FUNCTIONS ******************************/
/*
 * The function gets type, x, y and returns
 * the value (by type) of the node in position x,y.
 */
int getNodeValByType(Game* gp, valType_e valType, int x, int y);

/*
 * The function gets type, x, y, val and sets
 * the value (by type) of the node in position x,y.
 */
void setNodeValByType(Game* gp, valType_e valType, int x, int y, int val) ;

/************************* CHECK TABLE FUNCTIONS ******************************/


Game* initGame(int block_height, int block_width);
int setLatestAction(Game* gp, Action *action);
int isErroneousBoard(Game* gp);
void freeGame(Game* gp);
int UpdateErrors(Game *gp);
int clearBoardByValType(Game* gp, valType_e val_type);
int CountValuesInBoard(Game *game);

int updateErrorsFromCheckTable(Game *gp, int ***checkTable, int lenOfArr);
void freeCheckTable(int ***checkTable, int rowSize);
int ***callocCheckTable(int rowSize);
int resetCheckTable(int ***checkTable, int rowSize);

#endif /* GAME_H_ */
