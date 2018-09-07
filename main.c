#include "Game_structs.h"
#include "mainAux.h"
#include "settings.h"
#include "Game.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int exit = 0, execute = 0, iswin = 0;
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
			bzero(x, MAX_SIZE);
			bzero(y, MAX_SIZE);
			bzero(z, MAX_SIZE);

			command = getCommand(game->mode, x, y, z);
			printf("%s, %s, %s, %d \n", x, y, z, (int)command);
			if (command == exit_game) {
				exit = 1;
				break;
			} else {
				printf("executing in mode = %d\n", game->mode);
				execute = executeCommand(&game, command, x, y, z);
				printf("execute result is = %d\n",execute);
				iswin = isWin(game);
				printf("is win = %d\n",iswin);
				if (execute == -1){
					return -1;
				}
				if (iswin) {
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



