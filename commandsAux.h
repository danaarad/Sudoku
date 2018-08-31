/*
 * commandsAux.h
 *
 *  Created on: Aug 25, 2018
 *      Author: Dana Arad
 */

#ifndef COMMANDSAUX_H_
#define COMMANDSAUX_H_
#include "Game_structs.h"

#define RETRY_ATTEMPTS_FOR_GENERATE 1000
int validate_values_for_set(int x, int y, int z, char *z_str, int N);
int validate_values_for_generate(int x, char *x_str, int y, char *y_str, int E);
int validate_values_for_hint(int x, int y, int N);
int moveAutoFillToValue(Game *game);

#endif /* COMMANDSAUX_H_ */
