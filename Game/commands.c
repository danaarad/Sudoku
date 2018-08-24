/*
 * commands.c
 *
 *  Created on: 11 баев 2018
 *      Author: yael sapir
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "Game.h"
#include "file_handler.h"

int doSave(Game* gp, char *fileName){
	FILE* file_ptr = NULL;
		if (!isErrornousBoard(gp)){
			if (isSolvableBoard(gp)){
				file_ptr = fopen(fileName,"w");
				if (file_ptr != NULL){//success
					writeToFile(gp, file_ptr);
					printf("Saved to: %s\n",fileName);
					return 0;
				}else{//couldn't open file
					printf("Error: File cannot be created or modified\n");
				}
			}else{ //board is not solvable
				printf("Error: board validation failed\n");
			}
		}else{//there are bad values in the board
			printf( "Error: board contains erroneous values\n");
		}
	return 0;
	}
