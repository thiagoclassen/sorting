/*
 ============================================================================
 Name        : sorting.c
 Author      : Thiago
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void inserctionSort(int array[]);
void selectionSort(int array[]);

int main(void) {
	int array[10] = { 5, 4, 7, 2, 9, 1, 0, 6, 3, 5 };

	selectionSort(array);

	return EXIT_SUCCESS;
}

void inserctionSort(int array[]) {

	int i, j, temp;

	for (i = 1; i < 10; i++) {
		j = i - 1;
		while (array[j + 1] < array[j] && j >= 0) {
			temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;
			j--;
		}
	}

	for (i = 0; i < 10; i++) {
		printf("\n%d", array[i]);
	}
}

void selectionSort(int array[]) {
	int i, j, menorIdx, temp;

	for (i = 0; i < 9; i++) {
		menorIdx = i;
		for (j = i+1; j < 10; j++) {
			if (array[j] < array[menorIdx]) {
				menorIdx = j;
			}
		}
		temp = array[menorIdx];
		array[menorIdx] = array[i];
		array[i] = temp;
	}

	for (i = 0; i < 10; i++) {
		printf("\n%d", array[i]);
	}
}
