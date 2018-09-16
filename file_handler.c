/*
 * file_handler.c
 *
 *  contains file handling functions
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_handler.h"

#include "game.h"
#include "settings.h"

/*
 * Writes board into the given file.
 * The file is written according to the structure specified in the project assignment.
 */
int writeToFile (Game* gp, FILE *file_ptr){
	int blockHeight = gp->blockHeight, blockWidth = gp->blockWidth, N = gp->N;
	int x = 0, y = 0, val = 0;

	if (fprintf(file_ptr, "%d %d\n", blockHeight, blockWidth) < 0){
		printf(FSCANF_ERROR);
		return 0;
	}

	for(y = 0; y < N; y++){
		for(x = 0; x < N; x++){
			if(x > 0){
				if (fprintf(file_ptr," ") < 0){
					printf(FSCANF_ERROR);
					return 0;
				}
			}
			val = getNodeValByType(gp, VALUE, x, y);
			if (fprintf(file_ptr,"%d",val) < 0){
				printf(FSCANF_ERROR);
				return 0;
			}

			if(getNodeValByType(gp, ISGIVEN, x, y)||((gp->mode == EDIT) && val != 0)){
				if (fprintf(file_ptr,".") < 0){
					printf(FSCANF_ERROR);
					return 0;
				}
			}
		}
		if (fprintf(file_ptr,"\n") < 0){
			printf(FSCANF_ERROR);
			return 0;
		}
	}

	return 1;
}

/*
 * Returns a pointer to a new game as loaded from a given file.
 */
Game* readFromFile (FILE *file_ptr, int *error){
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
		printf("Error: Cannot read from file");
		*error = 0;
		return NULL;
	}
	gp = initGame(blockHeight, blockWidth);
	if (gp == NULL) {
		*error = -1;
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
