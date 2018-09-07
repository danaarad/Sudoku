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
#include "settings.h"
#include "Node.h"
#include "Game.h"

/*
 * Writes board into given file.
 * The file is written according to the structure specified in the project assignment.
 */
int writeToFile (Game* gp, FILE *file_ptr){
	int blockHeight = gp->blockHeight, blockWidth = gp->blockWidth, N = gp->N;
	int x = 0, y = 0, val = 0;

	fprintf(file_ptr, "%d %d\n", blockHeight, blockWidth);

	for(y = 0; y < N; y++){
		for(x = 0; x < N; x++){
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

/*
 * Returns a pointer to a new game as loaded from a given file.
 */
Game* readFromFile (FILE *file_ptr){
	char chr = '\0';
	char num_as_str[2] = {0};
	int num = 0, x = 0, y = 0, N = 0;
	int blockHeight = 0, blockWidth = 0;
	Game* gp = NULL;

	if (file_ptr == NULL) {
		return NULL;
	}

	/*get the size and set it*/
	num = fscanf(file_ptr, "%d %d\n", &blockHeight, &blockWidth);
	if (num != 2) {
		printf(SCANF_ERROR);
		return NULL;
	}
	gp = initGame(blockHeight, blockWidth);
	if (gp == NULL) {
		return NULL;
	}

	N = gp->N;
	for(y = 0; y < N; y++){
		for(x = 0; x < N; x++){
			num = 0;
			chr = fgetc(file_ptr);
			/*get all spaces before new num*/
			while(isspace(chr)){
				chr = fgetc(file_ptr);
			}

			/*get the number*/
			while(isdigit(chr)){
				num *= 10;
				num_as_str[0] = chr;
				num += atoi(num_as_str);
				chr = fgetc(file_ptr);
				/*in the last iteration this will be '.' or space of some kind*/
			}
			setNodeValByType(gp, VALUE, x, y, num);
			if(chr == '.') {
				setNodeValByType(gp, ISGIVEN, x, y, 1);
			}
		}
	}
	return gp;
}
