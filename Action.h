/*
 * Action.h
 *
 * Contains the Action and Changes interface
 * An action is used to save a "move" in the game in the undo/redo list
 * An action contains a singly-linked list of changes that were made to the board
 * An action also points to next and previous actions, thus implementing a doubly-linked list.
 *
 *This interface contains init and free functions, and also redo / undo and print functions.
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "game_structs.h"

/********************* FREE FUNCTIONS *********************/

/*
 * Recursively frees all Actions before the given Action (not included)
 */
void freeActionsBefore(Action *action);
/*
 * Recursively frees all Actions after the given Action (not included)
 */
void freeActionsAfter(Action *action);
/*
 * Frees a single Action.
 * Assumes before and after are free.
 */
void freeSingleAction(Action *action);
/*
 * Recursive free of Changes in Action.
 */
void freeChanges(Change *change);


/********************* INIT FUNCTIONS *********************/
/*
 * Returns a pointer to a new allocated Action with given paramaters.
 * See documentation of Action in Game_structs.h
 */
Action *initAction(actionType_e actionType,Change* changes, Action* prev_action);
/*
 * Creates a Change object with the given attributes and adds it after previous Change (prev).
 * This Change should be set after the last change in the Change chain.
 * See documentation of Change in Game_structs.h
 * Returns a pointer to the new Change.
 */
Change *initChange(int x, int y, int val_before, int val_after, Change *prev);


/********************* UNDO / REDO FUNCTIONS *********************/
/*
 * Undo the latest Action Change by Change.
 * Every Change is undone by changing the VALUE of node x,y from val_after to val_before.
 */
void undoAction(Game *gp);
/*
 * Redo the latest Action Change by Change.
 * Every Change is redone by changing the VALUE of node x,y from val_before to val_after.
 */
void redoAction(Game *gp);

/********************* PRINT FUNCTIONS *********************/
/*
 * print latest action changes for undo
 */
void printUndoChanges(Action *action);
/*
 * print latest action changes for redo
 */
void printRedoChanges(Action *action);
/*
 * Prints the correct message while redoing or undoing a change.
 */
void printChange(command_e command, actionType_e actionType, Change *change);


#endif /* ACTION_H_ */
