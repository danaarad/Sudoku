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
int fill_nodes_random(Game *game, valType_e val_type, int x);
int fill_nodes_ILP(Game *game, valType_e val_type);
int clear_nodes(Game *game, valType_e val_type, int y);
int exhaustive_backtracking(Game *game);
int get_possible_values_for_node(Game *game, valType_e valType, int x, int y, int *possible_values);

#endif /* SOLVER_H_ */
