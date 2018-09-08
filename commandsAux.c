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
	if (changes != NULL) {
		new_action = (Action *) initAction(action_type, changes, game->LatestAction);
		game->LatestAction = new_action;
		if (new_action == NULL) {
			return -1;
		}
	}
	return 1;

}
