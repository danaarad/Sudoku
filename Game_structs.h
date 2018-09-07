/*
 * Game_structs.h
 *
 *  Created on: 24 баев 2018
 *      Author: yael sapir
 */

#ifndef GAME_STRUCTS_H_
#define GAME_STRUCTS_H_

typedef enum command {
	exit_game = 0,
	print_board, validate,
	undo, redo,
	num_solutions, autofill,
	reset, mark_errors, save,
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
	TEMP,
	ISERROR
} valType_e;

typedef enum actionType {
	SET_A,
	GENERATE_A,
	INIT_A
} actionType_e;

typedef struct Node {
	int value;
	int isGiven;
	int tempValue;
	int isError;
}Node;

typedef struct Change {
	int x;
	int y;
	int val_before;
	int val_after;
	struct Change *next;
}Change;

typedef struct Action {
	actionType_e type;
	Change *changes;
	struct Action* prev_action;
	struct Action* next_action;
}Action;


typedef struct Game {
	int blockHeight;
	int blockWidth;
	int N;
	Node** gameBoard;
	mode_e mode;
	int markErrors;
	Action* LatestAction;
}Game;


#endif /* GAME_STRUCTS_H_ */
