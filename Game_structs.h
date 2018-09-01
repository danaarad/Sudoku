/*
 * Game_structs.h
 *
 *  Created on: 24 баев 2018
 *      Author: yael sapir
 */

#ifndef GAME_STRUCTS_H_
#define GAME_STRUCTS_H_

typedef enum command {
	print_board = 0, validate,
	undo, redo,
	num_solutions, autofill,
	reset, exit_game,
	mark_errors, save,
	generate, hint,
	set, solve, edit, not_found,
	edit_default
} command_e;

typedef enum Mode {
	INIT,
	SOLVE,
	EDIT
} mode_e;

typedef enum valType {
	VALUE,
	ISGIVEN,
	SOLUTION,
	TEMP,
	ISERROR
} valType_e;

typedef enum actionType {
	SET,
	GENERATE,
	RESET
} actionType_e;

typedef struct Node {
	int value;
	int isGiven;
	int solution;
	int tempValue;
	int isError;
}Node;


typedef struct Action {
	actionType_e type;
	int x;
	int y;
	int val_before_change;
	int val_after_change;
	struct Action* prev_action;
	struct Action* next_action;
	int is_prev_connected;
	int is_next_connected;
}Action;


typedef struct Game {
	int blockHeight;
	int blockWidth;
	Node** gameBoard;
	mode_e mode;
	int isErrornous;
	int isSolvable;
	int markErrors;
	Action* LatestAction;
	int filledNodes;
}Game;


#endif /* GAME_STRUCTS_H_ */
