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
	char *fname;
	int x = -1, y = -1, z = -1;
	int mark_errors = 1;

	printf("Sudoku\n------\n");

	/*while the user does not exit, start new game*/
	while(!exit) {
		game = (Game*) initGame(DEFAULT_BLOCK_HEIGHT, DEFAULT_BLOCK_WIDTH);
		if (game == NULL){
			return -1;
		}
		while (1) {
			fname = (char*) calloc(MAX_SIZE, sizeof(char));
			if (fname == NULL){
				printf(CALLOC_ERROR);
				return -1;
			}
			command = getCommand(game->mode, &x, &y, &z, fname);
			printf("%d, %d, %d, %s, %d, ", x, y, z, fname, (int)command);
			fflush(stdout);
			if (command == exit_game) {
				exit = 1;
				break;
			} else {
				if (command == solve) {
					game->mode = SOLVE;
				}
				if (command == edit || command == edit_default) {
					game->mode = EDIT;
				}
				if (isWin()) {
					game->mode = INIT;
				} else {
					printf("%d\n", game->mode);
					if (executeCommand(game, command, x, y, z, fname) == -1){
						return -1;
					}
				}
			}

		}
		if (exit == 1) {
			printf( "Exiting...");
		}

	}
	return 1;
}



