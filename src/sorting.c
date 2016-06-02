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

void inserctionSort();
void selectionSort();
void bubbleSort();
void shellSort();
void quickSort(int left, int right);

void startSeq();
void reallocSeq();

int size = 0;
int *seq;
int loadSequentialList();
void splitRG(char string[50]);
void insertSeqAtTheEnd(int rg);
int TAM = 1000;

void printList();

int main(void) {
	loadSequentialList();
//	quickSort(0,TAM-1);
//	shellSort();
//	inserctionSort();
	merge_sort(seq, TAM);
	printList();

	return EXIT_SUCCESS;
}

void startSeq() {
	free(seq);
	seq = (int*) malloc(size * sizeof(int));
}

void reallocSeq() {
	seq = (int *) realloc(seq, size * sizeof(int));
}

int loadSequentialList() {

	system("cls");
	printf("\n Carregando. . .\n");

	FILE *fp;
	fp = fopen("NomeRG1K.txt", "r");

	/* opening file for reading */
	if (fp == NULL) {
		perror("Error opening file");
		return (-1);
	}

	char string[50];

	while (fgets(string, 50, fp)) {
		splitRG(string);
	}

	fclose(fp);

	return 1;
}

void splitRG(char string[50]) {

	int i, j = 0, flag = 0, rg;
	char strRg[30];

	for (i = 0; i < 50 && string[i] != '\0'; i++) {
		if (string[i] != ',') {
			if (flag != 0) {
				strRg[j] = string[i];
			}
			j++;
		} else {
			j = 0;
			flag = 1;
		}
	}

	sscanf(strRg, "%d", &rg);

	insertSeqAtTheEnd(rg);
}

void insertSeqAtTheEnd(int rg) {

	size++;
	if (size == 1) {
		startSeq();
		seq[0] = rg;
	} else {
		reallocSeq();
		seq[size - 1] = rg;
	}
}

void printList() {
	int i;
	for (i = 0; i < TAM; i++) {
		printf("\n%d", seq[i]);
	}
}

void inserctionSort() {

	int i, j, temp;

	for (i = 1; i < TAM; i++) {
		j = i - 1;
		while (seq[j + 1] < seq[j] && j >= 0) {
			temp = seq[j];
			seq[j] = seq[j + 1];
			seq[j + 1] = temp;
			j--;
		}
	}
}

void selectionSort() {
	int i, j, menorIdx, temp;

	for (i = 0; i < TAM - 1; i++) {
		menorIdx = i;
		for (j = i + 1; j < TAM; j++) {
			if (seq[j] < seq[menorIdx]) {
				menorIdx = j;
			}
		}
		temp = seq[menorIdx];
		seq[menorIdx] = seq[i];
		seq[i] = temp;
	}
}

void bubbleSort() {
	int i, j, aux;

	for (i = TAM - 1; i >= 0; i--) {
		for (j = 0; j < i; j++) {
			if (seq[j] > seq[j + 1]) {
				aux = seq[j];
				seq[j] = seq[j + 1];
				seq[j + 1] = aux;
			}
		}
	}
}

void shellSort() {

	int i, j, k, tmp;

	for (i = TAM / 2; i > 0; i = i / 2) {
		for (j = i; j < TAM; j++) {
			for (k = j - i; k >= 0; k = k - i) {
				if (seq[k + i] >= seq[k])
					break;
				else {
					tmp = seq[k];
					seq[k] = seq[k + i];
					seq[k + i] = tmp;
				}
			}
		}
	}

//	int i, temp, j = TAM / 2, k;
//
//	for (i = 0; i < TAM; i++) {
//		k = i;
//		do {
//			if (seq[k] > seq[k + j]) {
//				temp = seq[k];
//				seq[k] = seq[k + j];
//				seq[k + j] = temp;
//			}
//			k += j;
//		} while (k+j < TAM);
//		j = j / 2;
//	}
}

void quickSort(int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = seq[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (seq[i] < pivot)
			i++;
		while (seq[j] > pivot)
			j--;
		if (i <= j) {
			tmp = seq[i];
			seq[i] = seq[j];
			seq[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(left, j);
	if (i < right)
		quickSort(i, right);
}

void merge(int *a, int n, int m) {
	int i, j, k;
	int *x = malloc(n * sizeof(int));
	for (i = 0, j = m, k = 0; k < n; k++) {

		if(j==n){
			x[k] = a[i++];
		}else if(i==m){
			x[k] = a[j++];
		}else if(a[j] < a[i]){
			x[k] = a[j++];
		}else{
			x[k] = a[i++];
		}

	}
	for (i = 0; i < n; i++) {
		a[i] = x[i];
	}
	free(x);
}

void merge_sort(int *a, int n) {

	if (n < 2)
		return;
	int m = n / 2;
	merge_sort(a, m);
	merge_sort(a + m, n - m);
	merge(a, n, m);
}

