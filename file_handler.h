/*
 * file_handler.h
 *
 *  Created on: 10 ���� 2018
 *      Author: yael sapir
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_
#include "Game_structs.h"

int writeToFile (Game *gp, FILE *file_ptr);
int readFromFile (char* filename);

#endif /* FILE_HANDLER_H_ */
