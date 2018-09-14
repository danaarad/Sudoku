/*
 * Game_structs.h
 *
 * Contains all of the structs and types for our Sudoku implementation
 * Contains to following structs:
 *
 * Node - each game board is a Node matrix. a Node has different values respective
 * to different layers of the game board.
 *
 * Change - a Change object is used to describe a change that was made to the board.
 * a Change contains the x and y of the cell and the values before and after the change.
 *
 * Action - an Action is used to save a "move" in the game in the undo/redo list.
 * an Action contains a singly-linked list of Changes that were made to the board
 * an Action also points to next and previous Actions, thus implementing a doubly-linked list.
 *
 * Game - an object that contains dimensions attributes,
 * a mark_error attribute, a board (Nodes matrix) and a pointer to the latest action.
 *
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
