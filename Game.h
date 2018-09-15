
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

/************************ GAME FUNCTIONS ***************************/
/*
 * Returns a pointer to a new game of size NxN (N = block_height*block_width);
 */
Game* initGame(int block_height, int block_width);

/*
 * All nodes have an ISERROR boolean value.
 * If one of the nodes has a true ISERROR field, it is an error and the board is erroneous.
 * In this case the function returns 1, else 0.
 */
int isErroneousBoard(Game* gp);

/*
 * Sets all values of type TEMP to 0 for all nodes.
 * This creates an alternative board with alternative values (currently 0).
 */
int clearBoardByValType(Game* gp, valType_e val_type);
/*
 * Returned number of filled nodes in board
 */
int CountValuesInBoard(Game *game);

/************************* ERROR HANDLING FUNCTIONS ******************************/
/*
 * Creates a check table for every row, col and block.
 * A check table is a 3D array that contains x,y values by value.
 * The check table is then sent to "updateErrorsFromCheckTable"
 * that updates the errors respectively.
 */
int UpdateErrors(Game *gp);

/************************* FREE FUNCTIONS ******************************/

/*
 * Frees the actions (and all the changes within),
 * Frees the game board (and all nodes within),
 * Frees the game.
 */
void freeGame(Game* gp);

#endif /* GAME_H_ */
