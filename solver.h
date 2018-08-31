/*
 * solver.h
 *
 *  Created on: Aug 31, 2018
 *      Author: Dana Arad
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "Game_structs.h"

int isSolvable(Game* gp);
int fill_nodes_random(Game *game, int x);
int fill_nodes_ILP(Game *game);
int clear_nodes(Game *game, int y);
int exhaustive_backtracking(Game *game);
int get_possible_values_for_node(Game *game, int x, int y, int *possible_values);
int isPossibleValue(Game* gp, valType_e valType, int x, int y, int valToCheck);

#endif /* SOLVER_H_ */
