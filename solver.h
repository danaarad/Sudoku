/*
 * solver.h
 *
 *  Created on: Aug 31, 2018
 *      Author: Dana Arad
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "Game_structs.h"

/*
 * Checks if board is solvable using LP.
 * Returns:
 *  1 if an optimal solution was found.
 * -1 if a memory error was encountered.
 *  0 else.
 */
int isSolvable(Game* gp);

/*
 * Fills num_of_cells cells with random values in the val_type field.
 * The function generates random x,y values,
 * if board[x][y] has a val_type value of 0, the function generates a random legal value.
 * When num_of_cells cells are full, the function returns 1.
 * if a cell with no possible values is found, the function returns 0.
 * upon memory error, the function returns -1.
 */
int fill_nodes_random(Game *game, valType_e val_type, int num_of_cells);

/*
 * Fills cells with solution using LP.
 * The function builds constraints from the board nodes val_type value,
 * runs Gurobi solve,
 * and translates Gurobi solution back to the board filling the val_type value of the nodes.
 *
 * Returns -1 on memory error else returns the Gurobi optimstatus
 */
int fill_nodes_ILP(Game *game, valType_e val_type);

/*
 * Clear num_to_clear values of type val_type from nodes in board game.
 * This function generates random x,y values
 * if board[x][y] does not have a val_type value of 0,it is set to 0.
 * When num_to_clear cells are cleared, the function returns 1.
 */
int clear_nodes(Game *game, valType_e val_type, int y);

/*
 * Performs the Exhaustive Backtracking algorithm as described in project documents
 * Nodes values of type VALUE are copied to values of type TEMP,
 * then the backtracking is performed on TEMP values.
 * Note that this function does not change values of type VALUE in the board.
 * Returns number of possible solutions for game.
 */
unsigned long exhaustive_backtracking(Game *game, int *error);

/*
 * possible_values[i] = 1 iff i+1 is possible (legal) for cell x,y in val_type board in game,
 * 						0 else.
 * Returns total number of possible values for cell
 */
int get_possible_values_for_node(Game *game, valType_e valType, int x, int y, int *possible_values);

#endif /* SOLVER_H_ */
