/*
 * commandsAux.c
 *
 *  Created on: Aug 25, 2018
 *      Author: Dana Arad
 */
#include <string.h>
#include <stdio.h>
#include "commandsAux.h"

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
	if (z == 0 && strcmp(z_str, "0") != 0) {
		return 0;
	}
	return 1;
}

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

int validate_values_for_hint(int x, int y, int N) {
	if (x < 1 || x > N) {
		return 0;
	}
	if (y < 1 || y > N) {
		return 0;
	}
}
int moveAutoFillToValue(Game *game) {
	int x = 0, y = 0;
	int N = game->blockHeight * game->blockWidth;
	int autofill_value = 0;
	int is_prev_connected = 0;
	Node *node_before, *node_after;
	Action *new_action;

	for (x = 0; x < N; ++x) {
		for (y = 0; y < N; ++y) {
			autofill_value = getNodeValByType(game, TEMP, x, y);
			if (autofill_value != 0) {
				node_before = (Node *) cloneNode((Node *) getNode(game, x, y));
				setNodeValByType(game, VALUE, x , y, autofill_value);
				node_after = (Node *) cloneNode((Node *) getNode(game, x, y));

				if (node_before == NULL || node_after == NULL) {
					printBoard(game, VALUE);
					return 0;
				}
				new_action = (Action *) initAction(x, y, node_before, node_after, game->LatestAction, is_prev_connected);
				if (new_action == NULL) {
					printBoard(game, VALUE);
					return 0;
				}
				is_prev_connected = 1;
			}
		}
	}
	return 1;

}
