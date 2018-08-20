/*
 * file_handler.c
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#include "MainAux.h"
#include "Game.h"
#include "settings.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printBoard(Game* gp, valType_e valType, int markErrorsOn, int toFileModeOn, FILE* file_ptr);

int writeToFile (Game* gp, FILE *file_ptr){
	int BLOCK_HEIGHT = gp->blockHeight, BLOCK_WIDTH = gp->blockWidth;

	fprintf(file_ptr, "%d %d\n", BLOCK_HEIGHT, BLOCK_WIDTH);
	printBoard(gp, VALUE, 0, 1, file_ptr);
	fclose(&file_ptr);
	return 1;
}

Game* ReadFromFile (FILE *file_ptr){
	char* line;
	int blockHeight=0, blockWidth=0;
	Game* gp;

	fscanf(file_ptr, "%d %d", &blockHeight, &blockWidth);//get the size and set it
	gp = initBoard(blockHeight, blockWidth);




	return gp;
}
