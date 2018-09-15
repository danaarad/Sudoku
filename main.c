/*
 *
 * sudoku-console by Yael Sapir and Dana Arad
 *
 *
 * Entry point for the program,
 * Runs the main game loop
 *
 *
 */


#include "Game_structs.h"
#include "commands.h"
#include "settings.h"
#include "Game.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>

/*
 * Returns 1 if game board is solved successfully
 * 		   0 if board is erroneous of not full
 */
static int isWin(Game *game) {
	int N = game->blockHeight * game->blockWidth;
	if (CountValuesInBoard(game) == (N * N)){
		if (game->mode == SOLVE) {
			if (isErroneousBoard(game) == 0) {
				printf("Puzzle solved successfully\n");
				return 1;
			} else {
				printf("Puzzle solution erroneous\n");
				return 0;
			}
		}
	}

	return 0;
}


int main() {
	int exit = 0;
	Game *game;
	command_e command;
	char  x[MAX_SIZE] = {0};
	char  y[MAX_SIZE] = {0};
	char  z[MAX_SIZE] = {0};

	srand(time(NULL));

	printf("Sudoku\n------\n");

	/*while the user does not exit, start new game*/
	while(!exit) {
		game = (Game*) initGame(DEFAULT_BLOCK_HEIGHT, DEFAULT_BLOCK_WIDTH);
		if (game == NULL){
			return -1;
		}
		while (1) {
			/*Init x y z*/
			bzero(x, MAX_SIZE);
			bzero(y, MAX_SIZE);
			bzero(z, MAX_SIZE);

			/*Get the command from the user*/
			command = getCommand(game->mode, x, y, z);

			/*Execute the command*/
			if (command == exit_game) {
				exit = 1;
				break;
			} else {
				if (executeCommand(&game, command, x, y, z) == -1){
					return -1;
				}
				/*Check if the user won the game*/
				if ((command == set ||
					 command == autofill ||
					 command == redo)
						&& isWin(game)) {
					freeGame(game);
					break;
				}
			}
		}
		if (exit == 1) {
			printf( "Exiting...\n");
			freeGame(game);
		}

	}
	return 1;
}



