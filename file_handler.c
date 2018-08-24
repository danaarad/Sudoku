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
	char type;
	int num;
	int BLOCK_WIDTH=0, BLOCK_HEIGHT=0;
	Game* gp;

	fscanf(file_ptr, "%d %d", &BLOCK_HEIGHT, &BLOCK_WIDTH);//get the size and set it
	gp = initBoard(BLOCK_HEIGHT, BLOCK_WIDTH);

	int i = 0, j = 0, k = 0, l = 0, x = 0, y = 0;
	mode_e mode = INIT;

	/* i is my block y this runs for every block n the col*/
	for (i = 0; i < BLOCK_WIDTH; ++i) {
		fscanf(file_ptr, %s);/*seperator*/
		/* j is my local y  this runs for every block n the row*/
		for (j = 0; j < BLOCK_HEIGHT; ++j) {
			fgetc(file_ptr);/*"|"*/
			/*is my block x*/
			for (k=0; k<BLOCK_HEIGHT; ++k) {
				/*is my local x*/
				for(l=0; l<BLOCK_WIDTH; ++l) {
					x = (k * BLOCK_WIDTH) + l + 1;
					y = (i * BLOCK_HEIGHT) + j + 1;

					num = getNum(file_ptr,ftell(file_ptr));
					type = fgetc(file_ptr);
					if (num != 0) {
						setNodeValByType(gp, VALUE, x, y, num);

						switch(type){
						case '.':
							setNodeValByType(gp, ISGIVEN, x, y, 1);
							break;
						case ' ':


						if ((getNodeValByType(gp, ISGIVEN, x, y) == 1 && mode != EDIT) || (toFileModeOn == 1 && mode == EDIT)) {
							fprintf(file_ptr,".");
						}else if(getNodeValByType(gp, ISERROR, x, y) == 1 && markErrorsOn && !toFileModeOn){
							fprintf(file_ptr,"*");
						}else {
							fprintf(file_ptr," ");
						}
					} else {
						fprintf(file_ptr,"    ");
					}
				}
				fprintf(file_ptr,"|");
			}
			fprintf(file_ptr,"\n");
		}
	}
	printSeperator(file_ptr, BLOCK_HEIGHT, BLOCK_WIDTH);
	fflush(file_ptr);
}


	return gp;
}
