/*
 * printer.h
 *
 *
 * Prints the game board as described in the project documents.
 * If a value is fixed it is marked by '.'.
 * If a value is errneous and the "mark_errors" flag is on,
 * the value is marked by '*'.
 * If game mode is EDIT the "mark_errors" flag is ignored and errors are marked.
 *
 */

#ifndef PRINTER_H_
#define PRINTER_H_
#include "Game_structs.h"

void printBoard(Game* gp, valType_e valType);

#endif /* PRINTER_H_ */
