#include "printer.h"
#include "Node.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * Prints the separator according to block height and width.
 */
static void printSaperator(int block_h, int block_w) {
	int  i = 0;
	int numofchars = ( 4*block_h*block_w + block_h + 1 );

	for (i = 0; i < numofchars; ++i) {
		printf("-");
	}
	printf("\n");
	fflush(stdout);
}

/*
 * Prints the game board as described in the project documents.
 * If a value is fixed it is marked by '.'.
 * If a value is erroneus and the "mark_errors" flag is on,
 * the value is marked by '*'.
 * If game mode is EDIT the "mark_errors" flag is ignored and errors are marked.
 */
void printBoard(Game* gp, valType_e valType) {
	int i = 0, j = 0, k = 0, l = 0, x = 0, y = 0;
	int BLOCK_WIDTH = gp->blockWidth;
	int BLOCK_HEIGHT = gp->blockHeight;
	int markErrors = gp->markErrors;

	/* i is the block y this runs for every block n the col*/
	for (i = 0; i < BLOCK_WIDTH; ++i) {
		printSaperator(BLOCK_HEIGHT, BLOCK_WIDTH);
		/* j is the local y  this runs for every block n the row*/
		for (j = 0; j < BLOCK_HEIGHT; ++j) {
			printf("|");
			/*is the block x*/
			for (k = 0; k < BLOCK_HEIGHT; ++k) {
				/*is the local x*/
				for(l=0; l < BLOCK_WIDTH; ++l) {
					x = (k * BLOCK_WIDTH) + l;
					y = (i * BLOCK_HEIGHT) + j;

					if (getNodeValByType(gp, valType, x, y) != 0) {
						printf(" %2d",getNodeValByType(gp, valType, x, y));
						if (getNodeValByType(gp, ISGIVEN, x, y) == 1){
							printf(".");
						} else if(getNodeValByType(gp, ISERROR, x, y) == 1 &&
								(markErrors || gp->mode == EDIT)){
							printf("*");
						} else {
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
	printSaperator(BLOCK_HEIGHT, BLOCK_WIDTH);
}
