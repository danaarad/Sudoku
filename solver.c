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
#include <stdlib.h>
#include <stdio.h>

int isSolvable(Game* gp) {
	return 1;
}

int fill_nodes_random(Game *game, int num_of_cells) {
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
		if (getNodeValByType(game, VALUE, x, y) == 0) {
			possible_vals_arr = calloc(game->N, sizeof(int));
			if (possible_vals_arr == 0) {
				printf(CALLOC_ERROR);
				return 0;
			}

			num_of_possible_vals = get_possible_values_for_node(game, VALUE, x, y, possible_vals_arr);
			if (num_of_possible_vals == 0) {
				return 0;
			}
			is_good_random_val = 0;
			while (is_good_random_val == 0) {
				random_val = rand() % (game->N);
				is_good_random_val = possible_vals_arr[random_val];
			}
			setNodeValByType(game, VALUE, x, y, random_val);
			free(possible_vals_arr);
			++filled;
		}
	}
	return 1;
}

int fill_nodes_ILP(Game *game) {
	return 1;
}

int clear_nodes(Game *game, int num_to_clear) {
	int x = 0;
	int y = 0;
	int cleared = 0;

	while (cleared < num_to_clear) {
		x = rand()%(game->N);
		y = rand()%(game->N);
		if (getNodeValByType(game, VALUE, x, y) != 0) {
			setNodeValByType(game, VALUE, x, y, 0);
			++cleared;
		}
	}
	return 1;
}

int exhaustive_backtracking(Game *game){
	int x = 0, y = 0;
	int value = 1;
	int game_value = 0;
	int num_of_solutions = 0;
	stack_node *top = NULL;
	int counter = 0;

	moveValueToTemp(game);
	do {
		++counter;
		printf("counter = %d\n", counter);
		printf("x = %d y = %d value = %d\n", x, y, value);
		printBoard(game, TEMP);
		fflush(stdout);

		game_value = getNodeValByType(game, VALUE, x, y);
		if (value > game->N) {
			if (game_value == 0) {
				setNodeValByType(game,TEMP, x, y, 0);
			}
			top = (stack_node *) pop(top, &x, &y, &value);
			++value;
			continue;
		}


		if (game_value == 0) {
			//get possible value
			if (isPossibleValue(game, TEMP, x, y, value) != 1) {
				++value;
				continue;
			}
		} else {
			value = game_value;
		}

		//fill node with chosen value
		setNodeValByType(game, TEMP, x, y, value);
		//continue backtracking
		if (x == (game->N - 1) && y == (game->N - 1)) {
			printf("end of board!\n");
			++num_of_solutions;
			if(game_value != 0) {
				setNodeValByType(game, TEMP, x, y, 0);
			}
			top = (stack_node *) pop(top, &x, &y, &value);
			++value;
		} else if (x == (game->N - 1)) {
			printf("end of line!\n");
			top = (stack_node *) push(top, x, y, value);
			x = 0;
			y += 1;
			value = 1;
		} else {
			top = (stack_node *) push(top, x, y, value);
			x += 1;
			value = 1;
			printf("moving to %d %d!\n", x, y);
		}
	} while (top != NULL && counter < 100);
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

int isPossibleValue(Game* gp, valType_e valType, int x, int y, int valToCheck){
	int i = 0, j = 0, x_corner = 0, y_corner = 0, otherVal = 0;
	int rowSize, colSize, blockWidth, blockHeight;
	blockWidth = gp->blockWidth;
	blockHeight = gp->blockHeight;
	rowSize = colSize = blockWidth*blockHeight;

	/*check row*/
	for (i = 0; i < rowSize; ++i){
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
