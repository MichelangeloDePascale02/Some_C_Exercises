#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#pragma warning(disable:4996) // used to disable warnings due to the use of scanf and gets without _s suffix in Visual Studio

#define MAX_LENGHT 250 // max lenght of the string the user can insert

int count_spaces(char* s);
int* space_positions(char* s, int spaces);

int main() {
	char sentence[MAX_LENGHT] = ""; 
	int n, i; // n is to memorize the number of spaces that are present in the inserted string
	printf("Insert the string you want to calculate the number of spaces\n"); 
	gets(sentence); // acquisition of the string

	n = count_spaces(sentence); // call of the function used to know the number of spaces

	int* spacePositionsPtr; // declaration of the pointer that is going to be used to print all the positions where there is a space
	spacePositionsPtr = space_positions(sentence, n); // call of the function used to know the position of spaces

	for (i = 0; i < n; i++) { // array display cycle in which the positions of the spaces are stored
		printf("%d\n", *spacePositionsPtr);
		spacePositionsPtr++;
	}

	free(spacePositionsPtr - n); // cleaning of the memory allocated to the malloc declared in the function spaces_positions()

	return 0;
}

int count_spaces(char* s) {
	char* cPtr;
	int spaces = 0;
	for (cPtr = s; cPtr < s + strlen(s); cPtr++) {
		if (*cPtr == ' ') { // if the character currently analyzed is a space
			spaces++; // increase the number of spaces found in the string
		}
	}
	return spaces;
}

int* space_positions(char* s, int spaces) {
	int i;
	int* p = (int*)malloc(sizeof(int) * spaces); // space allocation for our dynamic array which will have "n" positions as the spaces of the string
	if (p) // if (p) means that the pointer is not null and the malloc command is being executed correctly
	{
		for (i = 0; i < strlen(s); i++) {
			if (s[i] == ' ') { // if the character currently analyzed is a space
				*p = i; // memorize in a position of the vector we allocated before the position of the space in the string
				p++;
			}
		}
	}
	else // this else means that there is a problem allocating the space, maybe there is no memory left to use...
	{
		printf("We encountered some problems, please contact the developer\n");
	}
	return p - spaces;

}