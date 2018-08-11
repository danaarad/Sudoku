/*
 * file_handler.c
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#include "MainAux.h"
#include "Board.h"
#include "settings.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int writeToFile (FILE *file_ptr, mode_e mode){

	fprintf(file_ptr, "%d %d\n", BLOCK_HEIGHT, BLOCK_WIDTH);
	printBoard(file_ptr, 0, mode, 1);
	fclose(&file_ptr);

	printf("Saved to: %s\n",filename);
	return 1;
}

int ReadFromFile (FILE *file_ptr){
	char* line;

	fscanf(file_ptr, "%d %d", BLOCK_HEIGHT, BLOCK_WIDTH);//get the size and set it
	initBoard(BLOCK_HEIGHT, BLOCK_WIDTH);



	return 0;
}
