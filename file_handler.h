/*
 * file_handler.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_
#include "Game_structs.h"
#include <stdio.h>

int writeToFile (Game* gp, FILE *file_ptr);
Game* readFromFile (FILE *file_ptr, int *error);

#endif /* FILE_HANDLER_H_ */
