/*
 * file_handler.c
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_handler.h"
#include "Node.h"
#include "Game.h"


int writeToFile (Game* gp, FILE *file_ptr){
	int blockHeight = gp->blockHeight, blockWidth = gp->blockWidth;
	int x = 0, y = 0, val = 0, rowlen = blockWidth*blockHeight;

	fprintf(file_ptr, "%d %d\n", blockHeight, blockWidth);

	for(y = 0; y < rowlen; y++){
		for(x = 0; x < rowlen; x++){
			if(x > 0){
				fprintf(file_ptr," ");
			}
			val = getNodeValByType(gp, VALUE, x, y);
			fprintf(file_ptr,"%d",val);

			if(getNodeValByType(gp, ISGIVEN, x, y)||((gp->mode == EDIT) && val != 0)){
				fprintf(file_ptr,".");
			}
		}
		fprintf(file_ptr,"\n");
	}

	fclose(file_ptr);
	return 1;
}

Game* readFromFile (FILE *file_ptr){
	char chr;
	int num, x = 0, y = 0, rowlen;
	int blockHeight=0, blockWidth=0;
	Game* gp;

	fscanf(file_ptr, "%d %d\n", &blockHeight, &blockWidth);//get the size and set it
	gp = initGame(blockHeight, blockWidth);

	rowlen = blockWidth*blockHeight;
	for(y = 0; y < rowlen; y++){
		for(x = 0; x < rowlen; x++){
			num = 0;
			chr = fgetc(file_ptr);

			while(isdigit(chr)){
				num *= 10;
				num += atoi(&chr);
				chr = fgetc(file_ptr);
			}
			setNodeValByType(gp, VALUE, x, y, num);
			if(chr == '.'){
				setNodeValByType(gp, ISGIVEN, x, y, 1);
				setNodeValByType(gp, SOLUTION, x, y, num);
				chr = fgetc(file_ptr);//get empty space after dot
			}
		}
	}
	fclose(file_ptr);
	return gp;
}
