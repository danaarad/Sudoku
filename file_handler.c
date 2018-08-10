/*
 * file_handler.c
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#include "MainAux.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int writeToFile (char* filename){
	FILE* file_ptr = NULL;
	if (!isErrornousBoard()){
		if (isSolvableBoard()){
			file_ptr = fopen(filename,"w");
			if (file_ptr != NULL){//success
				printBoard(file_ptr);
				printf("Saved to: %s\n",filename);
				return 1;
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

int ReadFromFile (char* filename){
	FILE* file_ptr = NULL;
	file_ptr = fopen(filename,"r");
	return 0;
}
