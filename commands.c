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
#include "Board.h"
#include "file_handler.h"

int doSave(char *fileName, mode_e mode){
	FILE* file_ptr = NULL;
		if (!isErrornousBoard()){
			if (isSolvableBoard()){
				file_ptr = fopen(fileName,"w");
				if (file_ptr != NULL){//success
					return writeToFile(file_ptr, mode);
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

}
