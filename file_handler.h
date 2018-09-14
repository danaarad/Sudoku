/*
 * file_handler.h
 *
 * Contains file handling functions
 * writeToFile is used to write a game board to the given file pointer
 * readFromFile is used to read a game board from the given file pointer
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_
#include "Game_structs.h"
#include <stdio.h>

int writeToFile (Game* gp, FILE *file_ptr);
Game* readFromFile (FILE *file_ptr, int *error);

#endif /* FILE_HANDLER_H_ */
