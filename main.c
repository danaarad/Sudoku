#include "Game_structs.h"
#include "mainAux.h"
#include "settings.h"
#include "Game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int exit = 0;
	Game *game;
	command_e command;
	char  *x;
	char  *y;
	char  *z;

	printf("Sudoku\n------\n");

	/*while the user does not exit, start new game*/
	while(!exit) {
		game = (Game*) initGame(DEFAULT_BLOCK_HEIGHT, DEFAULT_BLOCK_WIDTH);
		if (game == NULL){
			return -1;
		}
		while (1) {
			x = (char*) calloc(MAX_SIZE, sizeof(char));
			y = (char*) calloc(MAX_SIZE, sizeof(char));
			z = (char*) calloc(MAX_SIZE, sizeof(char));
			if (x == NULL || y == NULL || z == NULL){
				printf(CALLOC_ERROR);
				return -1;
			}
			command = getCommand(game->mode, x, y, z);
			printf("%s, %s, %s, %d \n", x, y, z, (int)command);
			fflush(stdout);
			if (command == exit_game) {
				exit = 1;
				break;
			} else {
				if (executeCommand(game, command, x, y, z) == -1){
					return -1;
				}
				if (isWin()) {
					freeGame(game);
					break;
				}
			}
		free(x);
		free(y);
		free(z);
		}
		if (exit == 1) {
			free(x);
			free(y);
			free(z);
			freeGame(game);
			printf( "Exiting...");
		}

	}
	return 1;
}



