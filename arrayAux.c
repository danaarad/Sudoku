/*
 * arrayAux.c
 *
 *  Created on: Aug 31, 2018
 *      Author: Dana Arad
 */



int filled_cells(int *arr){
	int len = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	int filled_cells = 0;

	for(i = 0; i < len; ++i) {
		if (arr[i] != 0) {
			++filled_cells;
		}
	}

	return filled_cells;

}

int get_first_value(int *arr){
	int len = sizeof(arr) / sizeof(arr[0]);
	int i = 0;

	for(i = 0; i < len; ++i) {
		if (arr[i] != 0) {
			return arr[i];
		}
	}

	return -1;

}

int findFirstFreeCellIn2DArr(int **Arr2D, int lenOfArr){
	int i;
	for (i = 0; i < lenOfArr; i++){
		if (Arr2D[i][0] == -1){
			return i;
		}
	}
	return lenOfArr;
}
