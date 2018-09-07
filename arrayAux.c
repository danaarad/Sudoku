/*
 * arrayAux.c
 *
 *  Created on: Aug 31, 2018
 *      Author: Dana Arad
 */
#include <stdio.h>

/*
 * Returns the number of nonzero values in array.
 */
int filled_cells(int *arr, int len){
	int i = 0;
	int filled_cells = 0;

	for(i = 0; i < len; ++i) {
		if (arr[i] != 0) {
			++filled_cells;
		}
	}

	return filled_cells;

}

/*
 * Returns the index(+1) of the first nonzero value in array.
 */
int get_first_value(int *arr, int len){
	int i = 0;

	for(i = 0; i < len; ++i) {
		if (arr[i] == 1) {
			return i + 1;
		}
	}
	return -1;

}

/*
 * Returns the index of the first zero value in a 2d array.
 * This function is used for working with check tables.
 */
int findFirstFreeCellIn2DArr(int **Arr2D, int lenOfArr){
	int i;
	for (i = 0; i < lenOfArr; i++){
		if (Arr2D[i][0] == -1){
			return i;
		}
	}
	return lenOfArr;
}
