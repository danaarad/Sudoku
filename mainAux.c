
int getCommand(mode_e mode, char *command, int *x, int *y, int *z){

}

int executeCommand(mode_e mode, char *command, int *x, int *y, int *z) {

}


void printSeperator(FILE* file_ptr){
	int  i = 0;
	int numofchars = ( 4*BLOCK_HEIGHT*BLOCK_WIDTH + BLOCK_HEIGHT + 1 );

	for (i = 0; i < numofchars; ++i) {
		fprintf(file_ptr, "-");
	}
	printf("\n");
}

void printBoard(FILE* file_ptr) {

	int i = 0, j = 0, k = 0, l = 0, x = 0, y = 0;

	/* i is my block y */
	for (i = 0; i < BLOCKS_IN_COL; ++i) {
		printSeperator(file_ptr);
		/* j is my local y */
		for (j = 0; j < BLOCKS_IN_ROW; ++j) {
			fprintf(file_ptr,"|");
			/*is my block x*/
			for (k=0; k<BLOCK_HEIGHT; ++k) {
				/*is my local x*/
				for(l=0; l<BLOCK_WIDTH; ++l) {
					x = (k * BLOCK_WIDTH) + l + 1;
					y = (i * BLOCK_HEIGHT) + j + 1;

					if (getNodeValue(x,y) != 0) {
						fprintf(file_ptr," %2d",getNodeValue(x,y));
						if (getNodeGiven(x, y) == 1) {
							fprintf(file_ptr,".");
						}else if(getNodeError(x, y) == 1){
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
	printSeperator(file_ptr);
	fflush(file_ptr);
}

