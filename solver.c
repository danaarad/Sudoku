/*
 * solver.c
 *
 *  Created on: Aug 31, 2018
 *      Author: Dana Arad
 */
#include "solver.h"
#include "Node.h"
#include "Game.h"
#include "printer.h"
#include "stack.h"
#include "settings.h"
#include "gurobi_c.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Calls Linear programming, returns the optimstatus from gurobi.
 */
int isSolvable(Game *gp) {
	int solvable =  fill_nodes_ILP(gp, VALUE);
	if (solvable == -1) {
		return -1;
	}
	return solvable == GRB_OPTIMAL;
}

static int* BoardToGurobi(Game *gp, valType_e val_type){
	int N = gp->N;
	int num_vars = N*N*N;
	int r = 0, c = 0, v = 0, idx = 0;

	int *forGurobi = (int *)calloc(num_vars, sizeof(int));
	if (forGurobi == NULL) {
		printf(CALLOC_ERROR);
		return NULL;
	}

	for (c = 0; c < N; c++){
		for (r = 0; r < N; r++){
			v = getNodeValByType(gp, val_type, c, r);
			if (v != 0) {
				idx = vcrToidx(v, c, r, N);
				forGurobi[idx] = 1;
			}
		}
	}
	return forGurobi;
}

static int GurobiToSolution(Game *gp, double* solFromGurobi){
	int v = 0, c = 0, r = 0, idx = 0, count = 0;
	int N = gp->N;

	clearBoardByValType(gp, TEMP);
	for (c = 0; c < N; c++) {
		for (r = 0; r < N; r++) {
			for (v = 1; v <= N; v++) {
				idx = vcrToidx(v, c, r, N);
				if (solFromGurobi[idx] != 0) {
					setNodeValByType(gp, TEMP, c, r, v);
					count++;
				}
			}
		}
	}
	return count;
}

int fill_nodes_ILP(Game *gp, valType_e val_type){
	int N = gp->N;
	int num_values = N*N*N;
	int optimstatus = 0, count = 0;
	int *ConstrainsForGurobi = BoardToGurobi(gp, val_type);
	double *solsFromGurobi = (double *)calloc(num_values, sizeof(double));

	if (solsFromGurobi == NULL) {
		printf(CALLOC_ERROR);
		return -1;
	}

	if (ConstrainsForGurobi == NULL){
		return -1;
	}

	optimstatus = get_gurobi_solution(solsFromGurobi, ConstrainsForGurobi, gp->blockHeight, gp->blockWidth);
	if (optimstatus == -1) {
		return -1;
	} else if (optimstatus == GRB_OPTIMAL) {
		count = GurobiToSolution(gp, solsFromGurobi);
		if (count != N*N) {
			optimstatus = 0;
		}
	}

	free(solsFromGurobi);
	free(ConstrainsForGurobi);
	return optimstatus;
}

int fill_nodes_random(Game *game, valType_e val_type, int num_of_cells) {
	int x = 0;
	int y = 0;
	int filled = 0;
	int *possible_vals_arr;
	int num_of_possible_vals = 0;
	int random_val = 0;
	int is_good_random_val = 0;

	while (filled < num_of_cells) {
		x = rand()%(game->N);
		y = rand()%(game->N);
		if (getNodeValByType(game, val_type, x, y) == 0) {
			possible_vals_arr = calloc(game->N, sizeof(int));
			if (possible_vals_arr == NULL) {
				printf(CALLOC_ERROR);
				return -1;
			}

			num_of_possible_vals = get_possible_values_for_node(game, val_type, x, y, possible_vals_arr);
			if (num_of_possible_vals == 0) {
				free(possible_vals_arr);
				return 0;
			}

			is_good_random_val = 0;
			while (is_good_random_val != 1) {
				random_val = (rand() % (game->N));
				is_good_random_val = possible_vals_arr[random_val];
			}
			setNodeValByType(game, val_type, x, y, (random_val+1));
			++filled;
			free(possible_vals_arr);
		}
	}
	return 1;
}


int clear_nodes(Game *game, valType_e val_type, int num_to_clear) {
	int x = 0;
	int y = 0;
	int cleared = 0;

	while (cleared < num_to_clear) {
		x = rand()%(game->N);
		y = rand()%(game->N);
		if (getNodeValByType(game, val_type, x, y) != 0) {
			setNodeValByType(game, val_type, x, y, 0);
			++cleared;
		}
	}
	return 1;
}


static int moveValueToTemp(Game *game) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int value = 0;

	for (y = 0; y < N; ++y) {
		for (x = 0; x < N; ++x) {
			value = getNodeValByType(game, VALUE, x, y);
			setNodeValByType(game, TEMP, x , y, value);
		}
	}
	return 1;

}

static int isPossibleValue(Game* gp, valType_e valType, int x, int y, int valToCheck){
	int i = 0, j = 0, x_corner = 0, y_corner = 0, otherVal = 0;
	int rowSize, colSize, blockWidth, blockHeight;
	blockWidth = gp->blockWidth;
	blockHeight = gp->blockHeight;
	rowSize = colSize = blockWidth*blockHeight;

	/*check row*/
	for (i = 0; i < rowSize; ++i) {
		otherVal = getNodeValByType(gp, valType, i, y);
		if (otherVal == valToCheck && i != x){
			return 0;
		}
	}

	/*check col*/
	for (j = 0; j < colSize; ++j){
		otherVal = getNodeValByType(gp, valType, x, j);
		if (otherVal == valToCheck && j != y){
			return 0;
		}
	}

	/*check block*/
	x_corner = (x/blockWidth)*blockWidth;
	y_corner = (y/blockHeight)*blockHeight;
	for (i = x_corner; i < x_corner + blockWidth; ++i){
		for(j = y_corner; j < y_corner + blockHeight; ++j){
			otherVal = getNodeValByType(gp, valType, i, j);
			if (otherVal == valToCheck && (i != x || j != y)){
				return 0;
			}
		}
	}
	return 1;
}

unsigned long exhaustive_backtracking(Game *game, int *error){
	int x = 0, y = 0;
	int value = 1;
	int game_value = 0;
	unsigned long num_of_solutions = 0;
	stack_node *top = NULL;
	int backwards = 0;

	moveValueToTemp(game);
	do {
		/*get real value from board*/
		game_value = getNodeValByType(game, VALUE, x, y);

		/*if no legal value found, fold*/
		if (value > game->N) {
			/*if no real value, set cell to zero*/
			if (game_value == 0) {
				setNodeValByType(game,TEMP, x, y, 0); }
			/*fold*/
			top = (stack_node *) pop(top, &x, &y, &value);
			backwards = 1; ++value; continue; }

		if (game_value == 0) {
			/*get possible value for empty cell*/
			if (isPossibleValue(game, TEMP, x, y, value) != 1) {
				++value; continue; }
		} else {
			/*fold or continue if cell has real value*/
			if (backwards == 1) {
				top = (stack_node *) pop(top, &x, &y, &value);
				++value; continue; }
			value = game_value; }

		/*fill node with chosen value*/
		setNodeValByType(game, TEMP, x, y, value);

		/*continue backtracking*/
		if (x == (game->N - 1) && y == (game->N - 1)) {
			if(game_value == 0) {
				setNodeValByType(game, TEMP, x, y, 0);
			}
			top = (stack_node *) pop(top, &x, &y, &value);
			++num_of_solutions; backwards = 1; ++value;
		} else if (x == (game->N - 1)) {
			top = (stack_node *) push(top, x, y, value);
			/*check for push error*/
			if (top == NULL) {
				*error = -1; return 0; }
			backwards = 0; x = 0; y += 1; value = 1;
		} else {
			top = (stack_node *) push(top, x, y, value);
			/*check for push error*/
			if (top == NULL) {
				*error = -1; return 0; }
			backwards = 0; x += 1; value = 1;
		}
	} while (!(top == NULL && value > game->N));
	return num_of_solutions;
}


int get_possible_values_for_node(Game *game, valType_e valType, int x, int y, int *possible_values) {
	int val, count = 0;
	for(val = 1; val <= game->N; val++){
		possible_values[val-1] = isPossibleValue(game, valType, x, y, val);
		if (possible_values[val-1]){
			count++;
		}
	}
	return count;
}
