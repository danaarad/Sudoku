/*
 * file_handler.c
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#include "MainAux.h"
#include "Board.h"

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

int ReadFromFile (char* filename){
	FILE* file_ptr = NULL;
	file_ptr = fopen(filename,"r");


	return 0;
}
