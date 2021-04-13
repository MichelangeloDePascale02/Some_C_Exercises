/**
 * Matrix dynamic allocation
 * This program is used to sum the value of a dynamically allocated matrix
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int** allocMat(int, int); // this function is used to allocate the memory. It returns a pointer to the memory allocated
void fillMat(int**, int, int); // this function fills the matrix with casual numbers
int sumMat(int**, int, int); // this function sum all the matrix entries
void deallocMat(int**, int, int); // this function is used to free the memory allocated for the matrix

int main() {
	int row, column;

	// matrix dimension acquisition from stdin
	printf("Insert row's length: ");
	scanf_s("%d", &row);
	printf("\nInsert column's length: ");
	scanf_s("%d", &column);

	int** mat = (int**)allocMat(row, column); // memory allocation

	if (mat != NULL) {
		printf("\nMemory allocated correctly\n\n");
	}

	srand(time(0)); // randomize casual number
	fillMat(mat, row, column);
	printf(" %d", sumMat(mat, row, column)); // sum and print each number of the matrix

	deallocMat(mat, row, column); // memory deallocation

    puts("\n\nMemory has been deallocated");

	return 0;
}

int** allocMat(int r, int c) {
	int** m = (int**)malloc(sizeof(float*) * r); // allocate the rows

	if (m != NULL) {

		for (size_t i = 0; i < r; i++)
		{
			*(m + i) = (int*)malloc(sizeof(int) * c); // allocate all the column
		}
	}

	return m;
}

void fillMat(int** m, int r, int c) {
	puts("Numbers allocated: ");

	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = 0; j < c; j++) {
			m[i][j] = 1 + rand() % 50; // fill the matrix with casual number from 0 to 50 

			if (i == r - 1 && j == c - 1)
				printf("%d = ", m[i][j]);
			else 
				printf("%d + ", m[i][j]);
		}
	}
}

int sumMat(int** m, int r, int c) {

	int sum = 0;

	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = 0; j < c; j++) {
			sum += m[i][j]; // sum matrix's entries
		}
	}

	return sum;
}

void deallocMat(int** m, int r, int c) {

	if (m != NULL) {

		for (size_t i = 0; i < r; i++)
		{
			free(m[i]); // deallocate columns
		}

		free(m); // deallocate rows
	}
}