#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX 100

typedef struct user
{
	int userid;
	int age;
	char gender;
	int film_number;
	char job[20];
} User;

void sort_userList(User *l, const int);
void write_students_file(User *l, const int);

int main()
{
	int i = 0;
	FILE *filesPointer; // creating a file pointer to open the file we need to read
	if ((filesPointer = fopen("user.txt", "r")) == NULL)
	{ // if we cannot open the file, warn the user
		puts("The program has some problems opening the user file. Check if it is present in the directory of this source code. Or maybe you found a bug. Let the dev know!");
	}
	else
	{
		User userList[MAX]; // creating the array of struct that we can use to store users informations
		char row[64] = "";
		while (!feof(filesPointer))
		{

			fscanf(filesPointer, "%s", row); // reading a complete row from the txt file

			userList[i].userid = atoi(strtok(row, ",")); // then, we use the strtok() function to get the user's attributes
			userList[i].age = atoi(strtok(NULL, ","));
			userList[i].gender = strtok(NULL, ",")[0];
			userList[i].film_number = atoi(strtok(NULL, ","));
			strcpy(userList[i].job, strtok(NULL, ","));
			i++; // and of course we increment 'i' to point to the next user in the list
		}
		fclose(filesPointer); // closing the file, as is not necessary from now on
		puts("The file has been read successfully!");

		sort_userList(userList, MAX); // calling the function to sort the array of struct accortding to the user's age
		puts("The informations has been ordered successfully!");

		write_students_file(userList, MAX); // finally, we call the function to write in a file called "student.txt" the records that contain a student
	}
	return 0;
}

void sort_userList(User *l, const int card)
{
	int i, j;
	User swap;
	for (i = 0; i < card - 1; i++)
	{
		for (j = i + 1; j < card; j++)
		{ // simple sort algorithm: if the user in the next position is younger than the user we are analyzing, we swap positions
			if (l[j].age < l[i].age)
			{
				swap = l[j];
				l[j] = l[i];
				l[i] = swap;
			}
		}
	}
}

void write_students_file(User *l, const int card)
{
	FILE *filesPointer; // creating a file pointer to open the file we need to write
	if ((filesPointer = fopen("student.txt", "w")) == NULL)
	{ // if we cannot open the file, warn the user
		puts("The program has some problems opening the user file. Check if it is present in the directory of this source code. Or maybe you found a bug. Let the dev know!");
	}
	else
	{
		int i;
		for (i = 0; i < card; i++)
		{
			if (!strcmp(l[i].job, "student"))
			{ // if the l[i] user is a student, write its attributes in the newly created file
				fprintf(filesPointer, "%d,%d,%c,%d,%s\n", l[i].userid, l[i].age, l[i].gender, l[i].film_number, l[i].job);
			}
			printf("Analyzing and exporting student.txt: %d of %d...\n", i + 1, MAX);
		}
		fclose(filesPointer); // closing the file
	}
}
