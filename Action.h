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
#include "Game_structs.h"

void freeActionsBefore(Action *action);
void freeActionsAfter(Action *action);
void freeSingleAction(Action *action);
void freeChanges(Change *change);

Action *initAction(actionType_e actionType,Change* changes, Action* prev_action);
Change *initChange(int x, int y, int val_before, int val_after, Change *prev);

void undoAction(Game *gp);
void redoAction(Game *gp);

void printUndoChanges(Action *action);
void printRedoChanges(Action *action);
void printChange(command_e command, actionType_e actionType, Change *change);


#endif /* ACTION_H_ */
