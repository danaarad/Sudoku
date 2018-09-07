/*
 * commandsAux.c
 *
 *  Created on: Aug 25, 2018
 *      Author: Dana Arad
 */
#include <string.h>
#include <stdio.h>
#include "commandsAux.h"
#include "printer.h"
#include "Action.h"
#include "Node.h"
#include "Game.h"
#include "change.h"

/*
 * Varifies that x, y, and the set value (z) are valid values (between 0 and N = block_height*block_width);
 */
int validate_values_for_set(int x, int y, int z, char *z_str, int N) {
	if (x < 1 || x > N) {
		return 0;
	}
	if (y < 1 || y > N) {
		return 0;
	}
	if (z < 0 || z > N) {
		return 0;
	}
	/*since atoi might return 0 on success if the string was 0*/
	if (z == 0 && strcmp(z_str, "0") != 0) {
		return 0;
	}
	return 1;
}

/*
 * Varifies that nuber of cells to be filled (x param)
 * and number of cells to be cleared (y param) are valid values (between 0 and E = empty cells);
 */
int validate_values_for_generate(int x, char *x_str, int y, char *y_str, int E) {
	if (x < 0 || x > E) {
		return 0;
	}
	if (x == 0 && strcmp(x_str, "0") != 0) {
		return 0;
	}
	if (y < 0 || y > E) {
		return 0;
	}
	if (y == 0 && strcmp(y_str, "0") != 0) {
		return 0;
	}
	return 1;
}

/*
 * Varifies that x and y are valid values (between 1 and N = block_height*block_width);
 */
int validate_values_for_hint(int x, int y, int N) {
	if (x < 1 || x > N) {
		return 0;
	}
	if (y < 1 || y > N) {
		return 0;
	}
	return 1;
}

/*
 * Moves the TEMP value to the VALUE of all nonzero tempValues in board.
 * This represents a multiple change move (such as autofill and generate).
 * Therefore, each updated value is saved as a change and added to the new action.
 * This action will become the new latest action.
 */
int moveTempToValue(Game *game, actionType_e action_type) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int temp_value = 0;
	int val_before;
	Action *new_action = NULL;
	Change *changes = NULL;
	Change *new_change = NULL;

	for (y = 0; y < N; ++y) {
		for (x = 0; x < N; ++x) {
			temp_value = getNodeValByType(game, TEMP, x, y);
			if (temp_value != 0) {
				val_before = getNodeValByType(game, VALUE, x, y);
				setNodeValByType(game, VALUE, x , y, temp_value);

				new_change = initChange(x, y, val_before, temp_value, new_change);
				if (new_change == NULL) {
					printBoard(game, VALUE);
					return -1;
				}
				if (changes == NULL) {
					changes = new_change;
				}
			}
		}
	}
	new_action = (Action *) initAction(action_type, changes, game->LatestAction);
	game->LatestAction = new_action;
	if (new_action == NULL) {
		return -1;
	}
	return 1;

}
