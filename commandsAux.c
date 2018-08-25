/*
 * commandsAux.c
 *
 *  Created on: Aug 25, 2018
 *      Author: Dana Arad
 */
#include <string.h>
#include <stdio.h>

int validate_values_for_set(int x, int y, int z, char *z_str, int N) {
	if (x < 1 || x > N) {
		return 0;
	}
	if (y < 1 || y > N) {
		return 0;
	}
	if (z < 0 || z > N) {
		return 0;
	}
	if (z == 0 && strcmp(z_str, "0") != 0) {
		return 0;
	}
	return 1;
}
