#include "mainAux.h"
#include "../Game/Game.h"
#include "../Game/Node.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void printSeperator(int BLOCK_HEIGHT, int BLOCK_WIDTH){
	int  i = 0;
	int numofchars = ( 4*BLOCK_HEIGHT*BLOCK_WIDTH + BLOCK_HEIGHT + 1 );

	for (i = 0; i < numofchars; ++i) {
		printf("-");
	}
	printf("\n");
	fflush(stdout);
}


void printBoard(Game* gp, valType_e valType) {

	int i = 0, j = 0, k = 0, l = 0, x = 0, y = 0;
	int BLOCK_WIDTH = gp->blockWidth;
	BLOCK_HEIGHT = gp->blockHeight;
	markErrors = gp->markErrors;
	mode_e mode = gp->mode;

	/* i is my block y this runs for every block n the col*/
	for (i = 0; i < BLOCK_WIDTH; ++i) {
		printSeperator(BLOCK_HEIGHT, BLOCK_WIDTH);
		/* j is my local y  this runs for every block n the row*/
		for (j = 0; j < BLOCK_HEIGHT; ++j) {
			printf("|");
			/*is my block x*/
			for (k=0; k<BLOCK_HEIGHT; ++k) {
				/*is my local x*/
				for(l=0; l<BLOCK_WIDTH; ++l) {
					x = (k * BLOCK_WIDTH) + l + 1;
					y = (i * BLOCK_HEIGHT) + j + 1;

					if (getNodeValByType(gp, valType, x, y) != 0) {
						printf(" %2d",getNodeValByType(gp, valType, x, y));
						if (getNodeValByType(gp, ISGIVEN, x, y) == 1 && mode != EDIT){
							printf(".");
						}else if(getNodeValByType(gp, ISERROR, x, y) == 1 && markErrors){
							printf("*");
						}else {
							printf(" ");
						}
					} else {
						printf("    ");
					}
				}
				printf("|");
			}
			printf("\n");
		}
	}
	printSeperator(BLOCK_HEIGHT, BLOCK_WIDTH);
	fflush(stdout);
}
