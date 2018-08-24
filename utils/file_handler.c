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
	int x = 0, y = 0;

	fprintf(file_ptr, "%d %d\n", BLOCK_HEIGHT, BLOCK_WIDTH);

	for

	fclose(&file_ptr);
	return 1;
}

Game* ReadFromFile (FILE *file_ptr){
	char type;
	int num;
	int BLOCK_WIDTH=0, BLOCK_HEIGHT=0;
	Game* gp;

	fscanf(file_ptr, "%d %d", &BLOCK_HEIGHT, &BLOCK_WIDTH);//get the size and set it
	gp = initBoard(BLOCK_HEIGHT, BLOCK_WIDTH);


}


	return gp;
}
