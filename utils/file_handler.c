/*
 * file_handler.c
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#include "MainAux.h"
#include "Game.h"
#include "Node.h"
#include "settings.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
