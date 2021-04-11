#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char debugPrintfs;

unsigned long long lastZeros(unsigned long long N)
{
	unsigned long long zeros = 0; // counter variable that will store the number of zeros present at the end of the factorial of the number N received in input
	unsigned long long c = 5; // variable which we will use to store the powers of 5
	int before = 0, now = digitsOf(c);
	while (now >= before) {
		if (debugPrintfs == 'y') printf("Now dividing %20llu by %21llu\n",N , c);
		zeros += N / c; // dividing the number N by a power of 5, which increases for each iteration (5, 25, 125, 625, ...). In this way, we can calculate trailing zeros
		if(debugPrintfs=='y') printf("Partial trailing zeros found for now: %20llu\n", zeros);
		before = digitsOf(c); // calculating how much digits had c
		c *= 5; // multiplying c to get the next power of 5
		now = digitsOf(c); // calculating how much digits has c
		if (debugPrintfs == 'y') printf("Digits of current power - Before: %d Now: %d\n\n", before, now);
		if (c > N) break; // further exit condition if the number is not the greatest 64 bit, in this case we can stop when the current power of 5 is greater than N
	}
	return zeros;
}

int digitsOf(unsigned long long N) { // simple algorithm to calculate the number of digits of a number: it just keeps dividing the number by 10 and saving the result in the same variable until it reaches 0
	int digits = 0;
	while (N != 0) {
		N = N / 10;
		digits++;
	}
	return digits;
}

int main()
{
	char choice;
	puts("What do you want to do?\nType 'g' to know the number of trailing zeros of the factorial of a generic number");
	puts("Type 'b' to know the number of trailing zeros of the factorial of the greatest 64bit number");
	scanf_s("%c", &choice, 1);

	while ((getchar()) != '\n'); // used to clear the buffer, to prevent the program from skipping inputs

	puts("Would you like to enable the debugging printfs to check the value of the important variables for the program?\nType 'y' if you would.");
	scanf_s("%c", &debugPrintfs, 1);

	unsigned long long N;

	switch (choice) {
	case 'g':
		puts("Insert the number you want to know how many trailing zeros has its factorial");
		scanf_s("%llu", &N);
		printf("The factorial of %llu has %llu trailing zeros\n\n", N, lastZeros(N));
		break;

	case 'b':
		N = 18446744073709551615; //greatest 64bit integer value
		printf("The factorial of %llu, the greatest integer we can calculate, has %llu trailing zeros\n\n", N, lastZeros(N));
		break;

	default: 
		puts("You probably typed another character that the program can't use to make something useful. Please re-run the program paying attention to what you type");
		puts("If the problem is different, contact the dev. Maybe you found a bug!");
		break;
	}
}
